/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:12:06 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/01 01:46:51 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h> // ? For linux only
# include "libft.h"
# include "../src/minishell_builtins/builtins.h"
# include "../src/minishell_builtins/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

t_env	*get_envp(t_env *envp);

// # define DEBUG // ? debug

extern int	g_exit_status;

#endif // GLOBALS_H
