/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:49:19 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/28 20:00:21 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "globals.h"

void	exec_recur(t_ast_cmd *tree);
void	executor(t_ast_cmd *tree);

#endif // EXECUTOR_H
