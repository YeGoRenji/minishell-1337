/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:25 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/11 03:19:55 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast_cmd	*binary_node(t_node_type type, t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_binary	*node;

	node = malloc(sizeof(t_ast_binary));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*exec_node(t_token *argv_tok)
{
	t_ast_exec	*node;
	node = malloc(sizeof(t_ast_exec));
	if (!node)
		return (NULL);
	node->type = P_EXEC;
	node->argv_tok = argv_tok;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*redir_node(t_token_type direction, t_token *file_tok, int mode, int fd, t_ast_cmd *cmd)
{
	t_ast_redir	*node;
	node = malloc(sizeof(t_ast_redir));
	if (!node)
		return (NULL);
	node->type = P_REDIR;
	node->direction = direction;
	node->file_tok = file_tok;
	node->mode = mode;
	node->fd = fd;
	node->cmd = cmd;
	return ((t_ast_cmd *) node);
}

// ------------------------------------
// cmd1 args | cmd2 args && cmd3

void	print_got(char *str, t_token *lst_tok, t_token *lst_end) // Debug !
{
	printf("[%s] Got ", str);
	while (lst_tok != lst_end) {
		printf("%s ", lst_tok->value);
		lst_tok = lst_tok->next;
	}
	printf("\n");
}

t_token	*grab_token(t_token_type type, t_token *tokens, t_token *end)
{
	while (tokens && tokens->type != type && tokens != end)
		tokens = tokens->next;
	if (tokens == end)
		return (NULL);
	return (tokens);
}

bool	contains_token(t_token_type types[], t_token *token)
{
	int	i;
	t_token_type type = token->type;

	i = 0;
	while ((int)types[i] != -1)
	{
		if (type == types[i])
			return (true);
		i++;
	}
	return (false);
}

t_token	*grab_tokens(t_token_type types[], t_token *tokens, t_token *end)
{
	while (tokens && tokens != end)
	{
		if (contains_token(types, tokens))
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

void	null_terminate_lst(t_token *lst_tok, t_token *lst_end)
{
	while (lst_tok->next != lst_end)
		lst_tok = lst_tok->next;
	lst_tok->next = NULL;
}

t_ast_cmd	*parse_exec(t_token *lst_tok, t_token *lst_end)
{
	t_token	*exec;

	// Just to test
	exec = grab_token(WORD, lst_tok, lst_end);
	if (!exec)
		return (NULL);
	null_terminate_lst(lst_tok, lst_end);
	return (exec_node(lst_tok));
}

void free_tok(void *content)
{
	t_token *tok = content;
	free(tok->value);
	free(tok);
}

void	consume_redir(t_token *redir, t_token **lst_tok)
{
	t_token	*before_redir;

	if (redir == *lst_tok)
		*lst_tok = (*lst_tok)->next->next;
	else
	{
		before_redir = *lst_tok;
		while (before_redir->next != redir)
			before_redir = before_redir->next;
		before_redir->next = redir->next->next;
	}
	// ft_lstdelone(redir->next, free_tok);
	// ft_lstdelone(redir, free_tok);
}

t_ast_redir *tok_to_redir(t_token *redir_ptr)
{
	int			fd;
	int			mode;
	t_ast_redir	*redir;

	mode = 0;
	fd = 0;
	mode |= (redir_ptr->type == HEREDOC) * (O_CREAT | O_RDWR);
	mode |= (redir_ptr->type == INPUT) * (O_RDONLY);
	mode |= (redir_ptr->type == OUTPUT) * (O_CREAT | O_WRONLY);
	mode |= (redir_ptr->type == APPEND) * (O_CREAT | O_APPEND);
	fd += (redir_ptr->type == OUTPUT || redir_ptr->type == APPEND);
	redir = (t_ast_redir *)redir_node(
		redir_ptr->type,
		redir_ptr->next,
		mode,
		fd,
		NULL);
	return (redir);
}

t_ast_cmd	*parse_redir(t_token *lst_tok, t_token *lst_end)
{
	t_token			*redir_pos;
	t_ast_redir		*redir;

	print_got("parse_redir", lst_tok, lst_end);
	redir_pos = grab_tokens(
		(t_token_type[]){INPUT, HEREDOC, OUTPUT, APPEND, -1}, 
		lst_tok,
		lst_end
	);
	if (!redir_pos)
		return (parse_exec(lst_tok, lst_end));
	if (!redir_pos->next || redir_pos->next->type > DQSTR)
		return (NULL);
	redir = tok_to_redir(redir_pos);
	consume_redir(redir_pos, &lst_tok);
	// print_got("consumed to : ", lst_tok, lst_end);
	redir->cmd = parse_redir(lst_tok, lst_end);
	return ((t_ast_cmd *)redir);
}

t_ast_cmd	*parse_pipe(t_token *lst_tok, t_token *lst_end)
{
	t_token	*pipe_c;

	print_got("parse_pipe", lst_tok, lst_end);
	pipe_c = grab_token(PIPE, lst_tok, lst_end);
	if (pipe_c)
		return (binary_node(
			P_PIPE,
			parse_redir(lst_tok, pipe_c),
			parse_pipe(pipe_c->next, lst_end)
		));
	return (parse_redir(lst_tok, lst_end));
}

// TODO : Figure out how to do Parentheses
t_ast_cmd	*parse_cmd(t_token *lst_tok, t_token *lst_end)
{
	t_token		*or_and;

	print_got("parse_cmd", lst_tok, lst_end);
	or_and = grab_token(AND, lst_tok, lst_end);
	if (or_and)
		return (binary_node(
			P_AND,
			parse_cmd(lst_tok, or_and), 
			parse_cmd(or_and->next, lst_end)
		));
	or_and = grab_token(OR, lst_tok, lst_end);
	if (or_and)
		return (binary_node(
			P_OR,
			parse_cmd(lst_tok, or_and), 
			parse_cmd(or_and->next, lst_end)
		));

	return (parse_pipe(lst_tok, lst_end));
}

