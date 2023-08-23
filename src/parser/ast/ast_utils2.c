/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:56:35 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/23 22:46:32 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

void	free_tok_lst(t_token *tok)
{
	t_token	*tmp;

	if (!tok)
		return ;
	while (tok)
	{
		printf("Freeing %s\n", tok->value);
		free(tok->value);
		free_tok_lst(tok->nospace_next);
		tmp = tok;
		tok = tok->next;
		free(tmp);
	}
}

void	free_ast(t_ast_cmd *tree)
{
	t_ast_binary	*bin;
	t_ast_exec		*exec;
	t_ast_redir		*redir;

	if (!tree)
		return ;
	if (tree->type == P_EXEC)
	{
		exec = (t_ast_exec *)tree;
		free_tok_lst(exec->argv_tok);
	}
	else if (tree->type == P_REDIR)
	{
		redir = (t_ast_redir *)tree;
		free_tok_lst(redir->file_tok);
		free_ast(redir->cmd);
	}
	else
	{
		bin = (t_ast_binary *)tree;
		free_ast(bin->left);
		free_ast(bin->right);
	}
	free(tree);
}
