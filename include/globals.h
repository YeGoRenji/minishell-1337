/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:12:06 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/30 12:21:08 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h> // ? For linux only
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

char	**get_envp(char **envp);

// # define DEBUG // ? debug

#endif // STRUCTS_H
