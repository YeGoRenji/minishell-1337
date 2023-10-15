/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:40:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/15 15:30:08 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

static bool	check_empty_expand(char *file_name, char *first_tok_val)
{
	if (!file_name)
		return (false);
	if (!ft_strlen(file_name))
	{
		if ((*first_tok_val) == '$')
			print_err(first_tok_val, -4);
		else
			print_err(file_name, -5);
		return (false);
	}
	return (true);
}

static	void	wait_and_exit_status(int pid)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	set_exit_status(WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status) == 1 && WTERMSIG(exit_status) == 3)
	{
		ft_putendl_fd("Quit : 3", 2);
		set_exit_status(131);
	}
	else if (g_last_signal == 6969)
		set_exit_status(130);
}

void	exec_redir(t_ast_redir *tree, bool forked)
{
	int		fd_to_dup;
	int		fd_backup;
	char	*file_name;

	file_name = *expand_args(tree -> file_tok);
	if (!check_empty_expand(file_name, tree->file_tok->value))
		return ;
	fd_to_dup = open(file_name, tree->mode, 0644);
	if (fd_to_dup < 0)
		return (print_err(file_name, 0), set_exit_status(1));
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

void	exec_exe(t_ast_exec *exe, bool forked)
{
	char	**argv;
	pid_t	pid;
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
	if (!forked)
		pid = ft_fork();
	if (forked || !pid)
	{
		reset_default_sig_handlers();
		print_err(argv[0], execute_cmd(argv, envp));
		exit(get_exit_status());
	}
	wait_and_exit_status(pid);
	free_list(argv);
	if (forked)
		exit(get_exit_status());
}

void	exec_subsh(t_ast_subsh *tree, bool forked)
{
	pid_t	pid;
	int		exit_status;

	pid = ft_fork();
	if (!pid)
		executor(tree->cmd, true);
	waitpid(pid, &exit_status, 0);
	set_exit_status(WEXITSTATUS(exit_status));
	if (forked)
		exit(get_exit_status());
}
