/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:42:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/16 04:20:38 by ylyoussf         ###   ########.fr       */
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
	bool			to_expand;
	struct s_str	*next;
}	t_str;

char	**expand_args(t_token *argv_tok);
int		tok_lst_len(t_token *tok_lst);

/* String list utils */
void	ft_stradd_back(t_str **lst, t_str *new);
t_str	*new_str(char *str, bool to_expand);
void	free_strnode(t_str *node);
void	p_str_node(void *s);
void	ft_striter(t_str *lst, void (*f)(void *));
int		ft_strlstlen(t_str *lst);
t_str	*ft_strlast(t_str *lst);
void	ft_join_last(t_str **lst, char *str);
int	split_len(char **lst);

#endif
