/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:47:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/23 18:20:57 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

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
	// fprintf(stderr, "[%d] exe > \n", getpid());
	char	**argv;
	pid_t	pid;
	int		exit_status;
	t_env	*envp;

	argv = expand_args(exe->argv_tok);
	// printf("--uwu---\n");
	// int i = 0;
	// while (argv[i])
	// 	printf("%s\n", argv[i++]);
	// printf("--------\n");
	envp = get_envp(NULL);
	if (check_builtins(split_len(argv) - 1, argv[0], argv + 1))
	{
		if (forked)
			exit(g_exit_status);
		return (free_list(argv));
	}
	pid = fork();
	if (!pid)
	{
		// TODO: execute/call builtins
		print_err(argv[0], check_cmd(argv, envp));
		exit(g_exit_status);
	}
	// printf(" Waiting..\n");
	waitpid(pid, &exit_status, 0);
	g_exit_status = WEXITSTATUS(exit_status);
	// fprintf(stderr, "exe > Got ex_stat : %d\n", g_exit_status);
	free_list(argv);
}

void	exec_pipe(t_ast_binary *tree, bool forked)
{
	// fprintf(stderr, "[%d] pipe > \n", getpid());
	int		fd[2];
	pid_t	pids[2];
	int		exit_status;
	// TODO: create pipe then fork for both
	// TODO: dup the output and input
	pids[0] = pids[1] = 0;
	if (pipe(fd) == -1)
		exit(69);
	pids[0] = fork();
	if (!pids[0])
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			(print_err("dup", 0), exit(-1));
		close(fd[1]);
		executor((t_ast_cmd *)tree->left, true);
		exit(g_exit_status);
		// TODO: protecc ?
	}
	pids[1] = fork();
	if (!pids[1])
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			(print_err("dup", 0), exit(-1));
		close(fd[0]);
		executor((t_ast_cmd *)tree->right, true);
		exit(g_exit_status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[0], &exit_status, 0);
	waitpid(pids[1], &exit_status, 0);
	g_exit_status = WEXITSTATUS(exit_status);
	// fprintf(stderr, "pipe > Got ex_stat : %d\n", g_exit_status);
	if (forked)
		exit(g_exit_status);
}

void	exec_or(t_ast_binary *tree, bool forked)
{
	// fprintf(stderr, "[%d] or > \n", getpid());
	executor((t_ast_cmd *)tree->left, false);
	if (g_exit_status)
		executor((t_ast_cmd *)tree->right, false);
	if (forked)
		exit(g_exit_status);
}

void	exec_and(t_ast_binary *tree, bool forked)
{
	// fprintf(stderr, "[%d] and > \n", getpid());
	executor((t_ast_cmd *)tree->left, false);
	if (!g_exit_status)
		executor((t_ast_cmd *)tree->right, false);
	if (forked)
		exit(g_exit_status);
}

void	exec_redir(t_ast_redir *tree, bool	forked)
{
	fprintf(stderr, "[%d] redir > \n", getpid());
	char *redirs[4] = {">", ">>", "<", "<<"}; // ? Debug

	fprintf(stderr, " %s", redirs[tree->direction - 3]); // ? Debug
	print_nosp_tok(stdout, tree->file_tok);
	fprintf(stderr, " ");
	// TODO: open file
	// TODO: dup the output and input
	executor(tree->cmd, forked);
}

void	exec_subsh(t_ast_subsh *tree, bool forked)
{
	// fprintf(stderr, "[%d] subsh > \n", getpid());
	pid_t	pid;
	int		exit_status;
	// TODO: fork
	pid = fork();
	if (!pid)
		executor(tree->cmd, true);
	waitpid(pid, &exit_status, 0);
	g_exit_status = WEXITSTATUS(exit_status);
	// fprintf(stderr, "subsh > Got ex_stat : %d\n", g_exit_status);
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
