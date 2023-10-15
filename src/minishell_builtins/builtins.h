/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:59:15 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/11 14:24:28 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "builtin_utils.h"
# include "lst_operations.h"
# include "utils.h"

extern int	g_exit_status;

int			echo(int argc, char **args);
////// new stuff
int			cd(char *arg, t_env *env);
void		my_exit(char *arg);
int			export(int argc, char **argv, t_env **env);
int			unset(int argc, char **args, t_env **env);
int			env_(t_env **env);
int			pwd(void);
t_env		*search_in_env(t_env *env, char *key);
char		*pwd_trolling(char *str);
int			check_builtins(int argc, char *command, char **args);
char		**consume_env(t_env *env);
int			export(int argc, char **argv, t_env **env);;
#endif
