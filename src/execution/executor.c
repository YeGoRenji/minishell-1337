/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:47:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/30 04:02:27 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <sys/wait.h>

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

void	exec_exe(t_ast_exec *exe, bool forked)
{
	char	**argv;
	pid_t	pid;

	///// TODO: This is where stuff gets complicated
	///// TODO: Expand env
	// TODO: Prepare the argv
	argv = expand_args(exe->argv_tok);
	// TODO: Expand Wildcard
	if (forked)
	{
		print_err(argv[0], check_cmd(argv, get_envp(NULL)));
		exit(69);
	}
#ifdef DEBUG
	pid = fork();
	if (!pid)
	{
		// TODO: execute/call builtins
		// TODO: use jeff's envp linked list
		print_err(argv[0], check_cmd(argv, get_envp(NULL)));
		exit(69);
	}
	else
	{
		// printf(" Waiting..\n");
		waitpid(pid, NULL, 0);
	}
	free_split(argv);
#endif
}

void	exec_pipe(t_ast_binary *tree, bool forked)
{
	int		fd[2];
	pid_t	pids[2];
	// TODO: create pipe then fork for both
	// TODO: dup the output and input
	pids[0] = pids[1] = 0;
	if (pipe(fd) == -1)
		exit(69);
	forked = true;
	pids[0] = fork();
	if (!pids[0])
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		executor((t_ast_cmd *)tree->left, forked);
		// TODO: protecc ?
	}
	else
	{
		pids[1] = fork();
		if (!pids[1])
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			executor((t_ast_cmd *)tree->right, forked);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}

void	exec_or(t_ast_binary *tree, bool forked)
{
	executor((t_ast_cmd *)tree->left, forked);
	printf(" or ");
	// TODO: get exit status
	// if (exit_status isn't 0)
	executor((t_ast_cmd *)tree->right, forked);
}

void	exec_and(t_ast_binary *tree, bool forked)
{
	executor((t_ast_cmd *)tree->left, forked);
	printf(" and ");
	// TODO: get exit status
	// if (exit_status is 0)
	executor((t_ast_cmd *)tree->right, forked);
}

void	exec_redir(t_ast_redir *tree, bool	forked)
{
	char *redirs[4] = {">", ">>", "<", "<<"}; // ? Debug

	printf(" %s", redirs[tree->direction - 3]); // ? Debug
	print_nosp_tok(stdout, tree->file_tok);
	printf(" ");
	// TODO: open file
	// TODO: dup the output and input
	executor(tree->cmd, forked);
}

void	exec_subsh(t_ast_subsh *tree, bool forked)
{
	// TODO: fork
	printf("(");
	executor(tree->cmd, forked);
	printf(")");
}

void	executor(t_ast_cmd *tree, bool forked)
{
	if (!tree)
		return ;
	if (tree->type == P_AND)
		exec_and((t_ast_binary *)tree, forked);
	else if (tree->type == P_OR)
		exec_or((t_ast_binary *)tree, forked);
	else if (tree->type == P_PIPE)
		exec_pipe((t_ast_binary *)tree, forked);
	else if (tree->type == P_EXEC)
		exec_exe((t_ast_exec *)tree, forked);
	else if (tree->type == P_REDIR)
		exec_redir((t_ast_redir *)tree, forked);
	else if (tree->type == P_SUBSH)
		exec_subsh((t_ast_subsh *)tree, forked);
}
