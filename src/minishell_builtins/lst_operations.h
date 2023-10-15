/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_operations.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:03:16 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/10 22:55:57 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_OPERATIONS_H
# define LST_OPERATIONS_H
# include <libft.h>

t_env	*ft_lstnew(char *key, char *value, int equal_sign, t_env *prev);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_lstsize(t_env *lst);
void	ft_lstdelone(t_env *lst, void (*del)(void *));
t_env	*ft_lstlast(t_env *lst);
int		ft_lstsize(t_env *lst);
#endif
