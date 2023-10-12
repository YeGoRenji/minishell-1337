/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:47:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/12 14:26:52 by ylyoussf         ###   ########.fr       */
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
	char	**argv;
	pid_t	pid;
	int		exit_status;
	t_env	*envp;

	argv = expand_args(exe->argv_tok);
	log_last_command(argv[split_len(argv) - 1]);
	envp = get_envp(NULL);
	if (check_builtins(split_len(argv) - 1, argv[0], argv + 1))
	{
		if (forked)
			exit(get_exit_status());
		return (free_list(argv));
	}
	pid = fork();
	if (!pid)
	{
		reset_default_sig_handlers();
		print_err(argv[0], check_cmd(argv, envp));
		exit(get_exit_status());
	}
	waitpid(pid, &exit_status, 0);
	set_exit_status(WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status) == 1 && WTERMSIG(exit_status) == 3)
	{
		ft_putendl_fd("Quit : 3", 2);
		set_exit_status(131);
	}
	else if (g_last_signal == 6969)
		set_exit_status(130);
	free_list(argv);
	if (forked)
		exit(get_exit_status());
}

void	handle_dups(t_ast_cmd *sub_tree, int *fd, int fd_num)
{
	close(fd[!fd_num]);
	if (dup2(fd[fd_num], fd_num) == -1)
		(print_err("dup", 0), exit(-1));
	close(fd[fd_num]);
	executor(sub_tree, true);
	exit(get_exit_status());
}

void	exec_pipe(t_ast_binary *tree, bool forked)
{
	int		fd[2];
	pid_t	pids[2];
	int		exit_status;

	pids[0] = 0;
	pids[1] = 0;
	if (pipe(fd) == -1)
		exit(69);
	pids[0] = fork();
	if (!pids[0])
		handle_dups(tree -> left, fd, STDOUT_FILENO);
	pids[1] = fork();
	if (!pids[1])
		handle_dups(tree -> right, fd, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[0], &exit_status, 0);
	waitpid(pids[1], &exit_status, 0);
	set_exit_status(WEXITSTATUS(exit_status));
	if (forked)
		exit(get_exit_status());
}

void	exec_or(t_ast_binary *tree, bool forked)
{
	executor((t_ast_cmd *)tree->left, false);
	if (get_exit_status())
		executor((t_ast_cmd *)tree->right, false);
	if (forked)
		exit(get_exit_status());
}

void	exec_and(t_ast_binary *tree, bool forked)
{
	executor((t_ast_cmd *)tree->left, false);
	if (!get_exit_status())
		executor((t_ast_cmd *)tree->right, false);
	if (forked)
		exit(get_exit_status());
}

void	exec_redir(t_ast_redir *tree, bool forked)
{
	int	fd_to_dup;
	int	fd_backup;

	char *file_name = *expand_args(tree -> file_tok);
	if (!ft_strlen(file_name))
	{
		if ((*tree -> file_tok -> value) == '$')
			fprintf(stderr, "shell69: %s: ambiguous redirect\n", tree -> file_tok -> value);
		else
			fprintf(stderr, "shell69: %s: No such file or directory\n", file_name);
		return ;
	}
	fd_to_dup = open(file_name, tree->mode, 0644);
	if (fd_to_dup < 0)
		return (print_err(file_name, 0), set_exit_status(1), free(NULL));
	else
	{
		fd_backup = dup(tree->fd);
		if (fd_to_dup != tree->fd)
		{
			dup2(fd_to_dup, tree->fd);
			close(fd_to_dup);
		}
	}
	executor(tree->cmd, forked);
	if (fd_backup != tree->fd)
	{
		dup2(fd_backup, tree->fd);
		close(fd_backup);
	}
}

void	exec_subsh(t_ast_subsh *tree, bool forked)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (!pid)
		executor(tree->cmd, true);
	waitpid(pid, &exit_status, 0);
	set_exit_status(WEXITSTATUS(exit_status));
	if (forked)
		exit(get_exit_status());
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
