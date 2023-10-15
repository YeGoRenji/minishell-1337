/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatcher.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:01:34 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/11 14:24:45 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_DISPATCHER_H
# define BUILTIN_DISPATCHER_H
# include <libft.h>

int	echo(int argc, char **args);
int	pwd(void);
int	cd(char *arg, t_env *env);
#endif
