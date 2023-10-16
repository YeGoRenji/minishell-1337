/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:02:00 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/16 16:13:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_UTILS_H
# define GLOBAL_UTILS_H
# include "builtin_dispatcher.h"
# include "lst_operations.h"
# include <globals.h>
# include <libft.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stringbuilder.h>

int		export(int argc, char **argv, t_env **env);
int		env_(t_env **env);
int		unset(int argc, char **args, t_env **env);
int	my_exit(int argc, char *arg);
int		check_builtins(int argc, char *command, char **args);
char	*pwd_trolling(char *str);
char	*trim_path(char *pwd);
t_env	*search_in_env(t_env *env, char *key);
t_env	**get_envp_internal(t_env *envp);
t_env	*get_envp(t_env *envp);
char	**consume_env(t_env *env);
char	*get_env_value(char *var);
void	create_env(char **envp);
char	*get_key(char *line);
char	*get_value(char *line);
void	set_env_value(char *key, char *value, int equal_sign);
void	append_to_env(t_env **env, char *key, char *value, int equal_sign);
void	edit_env(t_env *node, char *value, int equal_sign);
int		is_concate(char *str);
t_env	*get_envp(t_env *envp);
t_env	**get_envp_internal(t_env *envp);
void	log_last_command(char *value);
int	validate_arg(char *arg);
char	*contruct_path(char **path);
#endif
