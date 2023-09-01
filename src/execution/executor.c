/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:47:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/01 02:51:58 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <sys/wait.h>

void	free_list(char **list)
{
	unsigned int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

void	exec_exe(t_ast_exec *exe, bool forked)
{
	printf("exe > \n");
	char	**argv;
	pid_t	pid;
	int		exit_status;
	t_env	*envp;

	///// TODO: This is where stuff gets complicated
	///// TODO: Expand env
	// TODO: Prepare the argv
	argv = expand_args(exe->argv_tok);
	// TODO: Expand Wildcard
	envp = get_envp(NULL);
	// if (check_builtins(tok_lst_len(exe->argv_tok) - 1, argv[0], argv + 1, &envp))
	// {
	// 	if (forked)
	// 		exit(g_exit_status);
	// 	else
	// 		return ;
	// }
	printf("WTF\n");
	if (forked)
	{
		print_err(argv[0], check_cmd(argv, envp));
		exit(-1);
	}
	printf("WTF 2\n");
	pid = fork();
	if (!pid)
	{
		// TODO: execute/call builtins
		printf("WTF IF\n");
		print_err(argv[0], check_cmd(argv, envp));
		exit(-1);
	}
	else
	{
	printf("WTF else\n");
		// printf(" Waiting..\n");
		waitpid(pid, &exit_status, 0);
		g_exit_status = WEXITSTATUS(exit_status);
		printf("exe > Got ex_stat : %d\n", g_exit_status);
	}
	printf("WTF 3\n");
	free_list(argv);
}

void	exec_pipe(t_ast_binary *tree, bool forked)
{
	printf("pipe > \n");
	int		fd[2];
	pid_t	pids[2];
	bool	do_exit;
	int		exit_status;
	// TODO: create pipe then fork for both
	// TODO: dup the output and input
	pids[0] = pids[1] = 0;
	do_exit = forked;
	if (pipe(fd) == -1)
		exit(69);
	forked = true;
	pids[0] = fork();
	if (!pids[0])
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			(print_err("dup", 0), exit(-1));
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
			if (dup2(fd[0], STDIN_FILENO) == -1)
				(print_err("dup", 0), exit(-1));
			close(fd[0]);
			executor((t_ast_cmd *)tree->right, forked);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[0], &exit_status, 0);
	waitpid(pids[1], &exit_status, 0);
	g_exit_status = WEXITSTATUS(exit_status);
	printf("pipe > Got ex_stat : %d\n", g_exit_status);
	if (do_exit)
		exit(g_exit_status);
}

void	exec_or(t_ast_binary *tree, bool forked)
{
	printf("or > \n");
	executor((t_ast_cmd *)tree->left, forked);
	if (g_exit_status)
		executor((t_ast_cmd *)tree->right, forked);
}

void	exec_and(t_ast_binary *tree, bool forked)
{
	printf("and > \n");
	executor((t_ast_cmd *)tree->left, forked);
	if (!g_exit_status)
		executor((t_ast_cmd *)tree->right, forked);
}

void	exec_redir(t_ast_redir *tree, bool	forked)
{
	printf("redir > \n");
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
	printf("subsh > \n");
	pid_t	pid;
	int		exit_status;
	// TODO: fork
	pid = fork();
	if (!pid)
		executor(tree->cmd, forked);
	waitpid(pid, &exit_status, 0);
	g_exit_status = WEXITSTATUS(exit_status);
	printf("subsh > Got ex_stat : %d\n", g_exit_status);
	if (forked)
		exit(g_exit_status);
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
