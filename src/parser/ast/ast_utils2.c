/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:56:35 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/27 10:43:13 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

void	free_ast(t_ast_cmd *tree)
{
	if (!tree)
		return ;
	if (tree->type == P_EXEC)
		free_tok_lst(((t_ast_exec *)tree)->argv_tok);
	else if (tree->type == P_REDIR)
	{
		free_tok_lst(((t_ast_redir *)tree)->file_tok);
		free_ast(((t_ast_redir *)tree)->cmd);
	}
	else if (tree->type == P_SUBSH)
		free_ast(((t_ast_subsh *)tree)->cmd);
	else
	{
		free_ast(((t_ast_binary *)tree)->left);
		free_ast(((t_ast_binary *)tree)->right);
	}
	free(tree);
}
