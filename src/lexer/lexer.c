/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:49:35 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/26 20:41:35 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void print_token(void *token) // Debug !
{
	t_token *tok = (t_token *)token;
	const char *token_types[] = { // Debug !
		"WORD",
		"STR",
		"DQSTR",
		"OUTPUT",
		"APPEND",
		"INPUT",
		"HEREDOC",
		"LPREN",
		"RPREN",
		"PIPE",
		"OR",
		"AND",
		"WHITE_SPACE",
		"NEW_LINE"
	};

	while (tok)
	{
		printf("[%s(%d)] %s%s", token_types[tok->type], tok->len, tok->value, tok->to_expand ? " EXPAND !" : "");
		if (tok->nospace_next)
			printf(" -> ");
		tok = tok->nospace_next;
	}
	printf("\n");
}

void	get_token(char *where, t_token *tok)
{
	tok->type = get_token_type(where);
	tok->len = get_token_len(tok->type, where);
}

bool	check_tok(t_token *this_tok, char *cmd_line,
		int index_space[2], t_token **tokens)
{
	if (this_tok->type < 0)
		return (tok_error(cmd_line[index_space[0]]), false);
	if (this_tok->type == WHITE_SPACE)
		return (true);
	if (this_tok->len == 1 &&
		(STR <= this_tok->type && this_tok->type <= DQSTR))
		return (unclosed_error(cmd_line[index_space[0]]), false);
	this_tok->value = ft_substr(cmd_line, index_space[0], this_tok->len);
	if (!this_tok->value)
		return (false);
	add_token(tokens,
		new_token(this_tok->type, this_tok->value, this_tok->len)
		, index_space[1]);
	return (true);
}

bool	lexer(char *command_line, t_token **tokens)
{
	int		index;
	bool	space;
	t_token	this_tok;

	printf("---- TOKENIZER ----\n"); // ? Debug !
	index = 0;
	*tokens = NULL;
	space = true;
	this_tok.type = WHITE_SPACE;
	if (!command_line)
		return (false);
	while (command_line[index])
	{
		space = this_tok.type == WHITE_SPACE;
		get_token(command_line + index, &this_tok);
		if (!check_tok(&this_tok, command_line,
				(int [2]){index, space}, tokens))
			return (free_tok_lst(*tokens), false);
		index += this_tok.len;
	}
	ft_tokadd_back(tokens, new_token(NEW_LINE, ft_strdup("newline"), 7));
	ft_tokiter(*tokens, print_token); // Debug !
	return (1);
}
