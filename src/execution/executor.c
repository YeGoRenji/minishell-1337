/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:47:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/28 20:48:53 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

void	exec_exe(t_ast_exec *exe)
{
#ifdef DEBUG
	t_token	*argv_tok;
	argv_tok = exe->argv_tok;
	while (argv_tok)
	{
		print_nosp_tok(stdout, argv_tok);
		fprintf(stdout, " ");
		argv_tok = argv_tok->next;
	}
#endif
	// TODO: This is where stuff gets complicated
	// TODO: Expand
	// TODO: Prepare the argv
	// TODO: execute/call builtins
}

void	exec_pipe(t_ast_binary *tree)
{
	// TODO: create pipe then fork for both
	// TODO: dup the output and input
	executor((t_ast_cmd *)tree->left);
	ft_putstr_fd(" pipe ", 1);
	executor((t_ast_cmd *)tree->right);
}

void	exec_or(t_ast_binary *tree)
{
	executor((t_ast_cmd *)tree->left);
	ft_putstr_fd(" or ", 1);
	// TODO: get exit status
	// if (exit_status isn't 0)
	executor((t_ast_cmd *)tree->right);
}

void	exec_and(t_ast_binary *tree)
{
	executor((t_ast_cmd *)tree->left);
	ft_putstr_fd(" and ", 1);
	// TODO: get exit status
	// if (exit_status is 0)
	executor((t_ast_cmd *)tree->right);
}

void	exec_redir(t_ast_redir *tree)
{
	char *redirs[4] = {">", ">>", "<", "<<"}; // ? Debug

	printf(" %s", redirs[tree->direction - 3]); // ? Debug
	print_nosp_tok(stdout, tree->file_tok);
	printf(" ");
	// TODO: open file
	// TODO: dup the output and input
	executor(tree->cmd);
}

void	exec_subsh(t_ast_subsh *tree)
{
	// TODO: fork
	printf("(");
	executor(tree->cmd);
	printf(")");
}

void	executor(t_ast_cmd *tree)
{
	if (!tree)
		return ;
	if (tree->type == P_AND)
		exec_and((t_ast_binary *)tree);
	else if (tree->type == P_OR)
		exec_or((t_ast_binary *)tree);
	else if (tree->type == P_PIPE)
		exec_pipe((t_ast_binary *)tree);
	else if (tree->type == P_EXEC)
		exec_exe((t_ast_exec *)tree);
	else if (tree->type == P_REDIR)
		exec_redir((t_ast_redir *)tree);
	else if (tree->type == P_SUBSH)
		exec_subsh((t_ast_subsh *)tree);
}
