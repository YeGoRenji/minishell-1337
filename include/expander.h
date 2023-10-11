/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:42:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/11 17:15:34 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "globals.h"
# include "lexer.h"
# include "stringbuilder.h"

# define TROLL 132

typedef struct s_str
{
	char			*str;
	bool			wild_card;
	struct s_str	*next;
}					t_str;

char				**expand_args(t_token *argv_tok);
char				*expand_env(char *to_expand, bool in_quote,
						bool ignore_env);
void				expand_nosp_arg(t_token *sub_tok, t_str **lst,
						bool ignore_env);
/* expander utils */
unsigned int		get_chunk_len(char *ptr, char *sp);
void				ghost_char_trolling(char *str);

/* wild_cards */
t_str	*expand_wild_cards(t_str *argv_lst);

/* String list utils */
void				ft_stradd_back(t_str **lst, t_str *new);
t_str				*new_str(char *str, bool to_expand);
void				free_strnode(t_str *node);
void				p_str_node(void *s);
void				ft_striter(t_str *lst, void (*f)(void *));
int					ft_strlstlen(t_str *lst);
t_str				*ft_strlast(t_str *lst);
void				ft_join_last(t_str **lst, char *str, bool to_expand);
int					split_len(char **lst);
char				**consume_argv(t_str *lst);
void				add_str_lst(char *str, t_str **lst, bool join_to_last, t_token *tok);

#endif /* EXPANDER_H */
