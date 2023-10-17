/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:49:19 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/17 15:00:49 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "error.h"
# include "expander.h"
# include "globals.h"
# include "signals.h"

void	executor(t_ast_cmd *tree, bool forked);
void	free_list(char **args);
int		execute_cmd(char **cmd, t_env *envp);
bool	check_absolute_path(char **cmd, t_env *env);
bool	check_if_executable(char **cmd, char *exec, char **paths, t_env *env);
char	*check_file_tok(t_token *file_tok);
pid_t	ft_fork(void);
/* binary */
void	exec_pipe(t_ast_binary *tree, bool forked);
void	exec_or(t_ast_binary *tree, bool forked);
void	exec_and(t_ast_binary *tree, bool forked);
/* unary */
void	exec_redir(t_ast_redir *tree, bool forked);
void	exec_exe(t_ast_exec *exe, bool forked);
void	exec_subsh(t_ast_subsh *tree, bool forked);
/* utils */
int		is_dir(char *str);

#endif /* EXECUTOR_H */
