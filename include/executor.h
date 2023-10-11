/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:49:19 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/11 14:16:17 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "expander.h"
# include "globals.h"
# include "signals.h"

void	executor(t_ast_cmd *tree, bool forked);
void	free_list(char **args);
int		check_cmd(char **cmd, t_env *envp);
int		print_err(char *preced, int msg_code);

#endif // EXECUTOR_H
