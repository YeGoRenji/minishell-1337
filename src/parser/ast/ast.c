/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:25 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/23 03:37:33 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast_cmd	*and_node(t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_and	*node;
	node = malloc(sizeof(t_ast_and));
	if (!node)
		return (NULL);
	node->type = P_AND;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*or_node(t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_or	*node;
	node = malloc(sizeof(t_ast_or));
	if (!node)
		return (NULL);
	node->type = P_OR;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*pipe_node(t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_pipe	*node;
	node = malloc(sizeof(t_ast_pipe));
	if (!node)
		return (NULL);
	node->type = P_PIPE;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*exec_node(char **argv)
{
	t_ast_exec	*node;
	node = malloc(sizeof(t_ast_exec));
	if (!node)
		return (NULL);
	node->type = P_EXEC;
	node->argv = argv;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*redir_node(char *file, int mode, int fd, t_ast_cmd *cmd)
{
	t_ast_redir	*node;
	node = malloc(sizeof(t_ast_redir));
	if (!node)
		return (NULL);
	node->type = P_REDIR;
	node->file = file;
	node->mode = mode;
	node->fd = fd;
	node->cmd = cmd;
	return ((t_ast_cmd *) node);
}

// ------------------------------------
// cmd1 args | cmd2 args && cmd3

void	print_got(char *str, t_list *lst_tok, t_list *lst_end) // Debug !
{
	printf("[%s] Got ", str);
	while (lst_tok != lst_end) {
		printf("%s ", ((t_token *)lst_tok->content)->value);
		lst_tok = lst_tok->next;
	}
	printf("\n");
}

t_list	*grab_token(t_token_type type, t_list *tokens, t_list *end)
{
	while (tokens && ((t_token *)tokens->content)->type != type && tokens != end)
		tokens = tokens->next;
	if (tokens == end)
		return (NULL);
	return (tokens);
}

t_ast_cmd	*parse_redir(t_list *lst_tok, t_list *lst_end)
{
	t_list	*redir;

	print_got("parse_redir", lst_tok, lst_end);
	printf("TODO: BE IMPLEMENTED\n");

	// Just to test
	redir = grab_token(WORD, lst_tok, lst_end);
	char *str = ((t_token *) redir->content)->value;
	char **lol = malloc(sizeof(char *));
	*lol = str;
	return (exec_node(lol));
}

t_ast_cmd	*parse_pipe(t_list *lst_tok, t_list *lst_end)
{
	t_list	*pipe_c;

	print_got("parse_pipe", lst_tok, lst_end);
	pipe_c = grab_token(PIPE, lst_tok, lst_end);
	if (pipe_c)
		return (pipe_node(
			parse_redir(lst_tok, pipe_c),
			parse_pipe(pipe_c->next, lst_end)
		));
	return (parse_redir(lst_tok, lst_end));
}

// TODO : Figure out how to do Parentheses
t_ast_cmd	*parse_cmd(t_list *lst_tok, t_list *lst_end)
{
	t_list		*or_and;

	print_got("parse_cmd", lst_tok, lst_end);
	or_and = grab_token(AND, lst_tok, lst_end);
	if (or_and)
		return (and_node(
			parse_cmd(lst_tok, or_and), 
			parse_cmd(or_and->next, lst_end)
		));
	or_and = grab_token(OR, lst_tok, lst_end);
	if (or_and)
		return (or_node(
			parse_cmd(lst_tok, or_and), 
			parse_cmd(or_and->next, lst_end)
		));

	return (parse_pipe(lst_tok, lst_end));
}

