/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:49:19 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/30 03:47:23 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "globals.h"
# include "expander.h"

void	executor(t_ast_cmd *tree, bool forked);
int		check_cmd(char **cmd, char **envp);
int		print_err(char *preced, int msg_code);

#endif // EXECUTOR_H
