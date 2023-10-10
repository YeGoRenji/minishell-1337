/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:53:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/10 15:36:16 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <globals.h>
#include <lexer.h>
#include <parser.h>
#include <signals.h>
#include <termios.h>

#define RED "\033[91m"
#define NOCOL "\033[0m"

enum { 
	INPUT_AT,
	OUTPUT_AT,
	ERROR_AT
};

void	chk(void)
{
	// system("leaks minishell");
}

int		g_exit_status;
int		g_last_signal;

void	prompt_pwd()
{
	printf("[" RED "%s" NOCOL "]\n", pwd_trolling(NULL));
}

void	tty_attr(struct termios *attrs, int action)
{
	if (action == SET)
	{
		tcgetattr(STDIN_FILENO, &attrs[0]);
		tcgetattr(STDOUT_FILENO, &attrs[1]);
		tcgetattr(STDERR_FILENO, &attrs[2]);
	}
	else if (action == RESET)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &attrs[0]);
		tcsetattr(STDOUT_FILENO, TCSANOW, &attrs[1]);
		tcsetattr(STDERR_FILENO, TCSANOW, &attrs[2]);
	}
}

int	main(int _, char **__, char **envp)
{
	t_token		*tokens;
	t_ast_cmd	*ast;
	char		*command_line;
	char		*tmp;
	struct termios	attrs[3];

	// TODO : Make an actual Prompt with PWD
	// atexit(chk); // ? Debug
	(void)_;
	(void)__;
	create_env(envp);
	tmp = getcwd(NULL, 0);
	rl_catch_signals = false;
	pwd_trolling(tmp);
	free(tmp);
	install_default_sig_handlers();
	tty_attr(attrs, SET);
	while (true)
	{
		if (g_last_signal != 69)
			prompt_pwd();
		command_line = readline("➤ ");
		g_last_signal = 0;
		if (!command_line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		lexer(command_line, &tokens);
		parser(tokens, command_line, &ast);
#ifdef DEBUG
		printf("----- EXECUTOR ----\n");
#endif
		executor(ast, false);
		if (*command_line)
			add_history(command_line);
		free_ast(ast);
		free(command_line);
		tty_attr(attrs, RESET);
	}
	free(command_line);
	exit(g_exit_status);
}
