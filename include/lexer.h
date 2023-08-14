/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 02:01:47 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/14 02:56:37 by ylyoussf         ###   ########.fr       */
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
	WHITE_SPACE,
	NEW_LINE
} t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	int				len;
	bool			to_expand;
	struct s_token	*nospace_next;
	struct s_token	*next;
} t_token;

bool 			lexer(char *command_line, t_token **tokens);
void			print_substr(int start, int end, char *str);
t_token_type	get_token_type(char *str);
int				get_token_len(t_token_type type, char *str);
// toklist
t_token	*ft_toklast(t_token *lst);
void	ft_tokadd_back(t_token **lst, t_token *new);
void	ft_tokiter(t_token *lst, void (*f)(void *));
t_token	*new_token(t_token_type type, char *value, int len);

#endif // LEXER_H
