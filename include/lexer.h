/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 02:01:47 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/19 19:00:57 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

typedef enum e_token_type {
	WORD = 0,
	STR,
	DQSTR,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
	LPREN,
	RPREN,
	PIPE,
	OR,
	AND,
	WHITE_SPACE
} t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	int				len;
	bool			to_expand;
	struct s_token	*nospace_next;
} t_token;

bool 			lexer(char *command_line, t_list **tokens);
void			print_substr(int start, int end, char *str);
t_token_type	get_token_type(char *str);
int				get_token_len(t_token_type type, char *str);

#endif // LEXER_H
