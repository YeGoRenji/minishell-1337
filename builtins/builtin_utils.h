/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:37:21 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/31 17:43:00 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H
# include "libft/libft.h"
# include <stddef.h>

int		consists_of(char *line, char c);
size_t	count(const char *s, int c);
t_env	*create_env(char **envp);
t_env	*search_in_env(t_env *env, char *key);
void	del_from_env(t_env **env, char *key);
int		validate_var_name(char *str);
void	print_exports(t_env *env);
void	print_env(t_env *env);
int ft_is_alphanum_underscore(char *str);
char *pwd_trolling(char *str);
#endif
