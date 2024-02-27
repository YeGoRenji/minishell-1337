/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:53:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/27 17:19:07 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <globals.h>
#include <lexer.h>
#include <parser.h>
#include <signals.h>
#include <termios.h>
#include <hacks.h>

#define RED "\033[0;91m"
#define NOCOL "\033[0m"

int		g_last_signal;

void	prompt_pwd(void)
{
	ft_putstr_fd("["RED, 1);
	ft_putstr_fd(pwd_trolling(NULL), 1);
	ft_putendl_fd(""NOCOL"]", 1);
}

void	tty_attr(struct termios *attrs, int action)
{
	if (action == ATTR_GET)
	{
		tcgetattr(STDIN_FILENO, &attrs[0]);
		tcgetattr(STDOUT_FILENO, &attrs[1]);
		tcgetattr(STDERR_FILENO, &attrs[2]);
	}
	else if (action == ATTR_SET)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &attrs[0]);
		tcsetattr(STDOUT_FILENO, TCSANOW, &attrs[1]);
		tcsetattr(STDERR_FILENO, TCSANOW, &attrs[2]);
	}
	else if (action == ATTR_CHG)
	{
		attrs[0].c_lflag &= ~ECHOCTL;
		attrs[1].c_lflag &= ~ECHOCTL;
		attrs[2].c_lflag &= ~ECHOCTL;
		tty_attr(attrs, ATTR_SET);
	}
}

void	setup_stuff(char **envp, struct termios *attrs, ...)
{
	char	*tmp;

	create_env(envp);
	tmp = getcwd(NULL, 0);
	rl_catch_signals = false;
	pwd_trolling(tmp);
	free(tmp);
	install_default_sig_handlers();
	tty_attr(attrs, ATTR_GET);
	tty_attr(attrs, ATTR_CHG);
}

bool	sabon_func(char *command_line)
{
	t_token			*tokens;
	t_ast_cmd		*ast;
	char			*dangling_kernel_pointer;

	if (!command_line)
	{
		ft_putendl_fd("exit", 1);
		return (free(command_line), true);
	}
	lexer(command_line, &tokens);
	if (parser(tokens, command_line, &ast))
		executor(ast, false);
	else
	{
		dup2(2, 0);
		g_last_signal = 0;
	}
	if (*command_line)
	{
		dangling_kernel_pointer = make_dangling(ft_strlen(command_line));
		set_env_value(ft_strdup("dick"), ft_strdup(dangling_kernel_pointer), 1);
		free(dangling_kernel_pointer);
		add_history(command_line);
	}
	return (free_ast(ast), free(command_line), false);
}

int	main(int _, char **__, char **envp)
{
	char			*command_line;
	struct termios	attrs[3];

	setup_stuff(envp, attrs, _, __);
	while (true)
	{
		if (g_last_signal != 69)
			prompt_pwd();
		command_line = readline("➤ ");
		if (sabon_func(command_line))
			break ;
		g_last_signal = 0;
		tty_attr(attrs, ATTR_SET);
	}
	exit(get_exit_status());
}
