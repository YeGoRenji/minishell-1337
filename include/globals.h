/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:12:06 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/06 14:06:13 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/wait.h>
# include "libft.h"
# include "../src/minishell_builtins/builtins.h"
# include <readline/readline.h>
# include <readline/history.h>

t_env	*get_envp(t_env *envp);

// # define DEBUG // ? debug

extern int	g_exit_status;

#endif // GLOBALS_H
