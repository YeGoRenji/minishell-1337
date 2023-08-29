/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:47:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/29 21:30:11 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

void	free_split(char **args)
{
	char	**head;

	head = args;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(*head);
	free(args);
}

void	exec_exe(t_ast_exec *exe)
{
	char	**argv;
	pid_t	pid;

	///// TODO: This is where stuff gets complicated
	///// TODO: Expand env
	// TODO: Prepare the argv
	// TODO: Expand Wildcard
	// TODO: execute/call builtins
	argv = expand_args(exe->argv_tok);
#ifdef DEBUG
	pid = fork();
	if (!pid)
	{
		execve(argv[0],
			argv,
			(char *[]){NULL});
		exit(69);
	}
	else
	{
		printf(" Waiting..\n");
		waitpid(pid, NULL, 0);
	}
	free_split(argv);
#endif
}

void	exec_pipe(t_ast_binary *tree)
{
	// TODO: create pipe then fork for both
	// TODO: dup the output and input
	executor((t_ast_cmd *)tree->left);
	printf(" pipe ");
	executor((t_ast_cmd *)tree->right);
}

void	exec_or(t_ast_binary *tree)
{
	executor((t_ast_cmd *)tree->left);
	printf(" or ");
	// TODO: get exit status
	// if (exit_status isn't 0)
	executor((t_ast_cmd *)tree->right);
}

void	exec_and(t_ast_binary *tree)
{
	executor((t_ast_cmd *)tree->left);
	printf(" and ");
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
