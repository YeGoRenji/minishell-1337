/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:12:06 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/31 22:51:58 by ylyoussf         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

t_env	*get_envp(t_env *envp);

// # define DEBUG // ? debug

int	g_exit_status;

#endif // GLOBALS_H
