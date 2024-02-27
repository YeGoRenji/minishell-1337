/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:12 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/27 20:49:40 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

# define DEBUG

void	debug_ast(t_ast_cmd *head, char *cmd);
void	debug_tree(t_ast_cmd *head, FILE *f, int index);

/* Utils */
void	debug_binary(t_ast_binary *head, FILE *f, int index);
void	debug_redir(t_ast_redir *head, FILE *f, int index);
void	debug_exec(t_ast_exec *head, FILE *f, int index);
void	debug_subsh(t_ast_subsh *head, FILE *f, int index);
