/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:53:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/07 16:19:06 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <globals.h>
#include <lexer.h>
#include <parser.h>
#include <signals.h>

#define RED "\033[91m"
#define NOCOL "\033[0m"

void	chk(void)
{
	// system("leaks minishell");
}

int		g_exit_status;


void	prompt_pwd()
{
	printf("[" RED "%s" NOCOL "]\n", pwd_trolling(NULL));
}

int	main(int _, char **__, char **envp)
{
	t_token		*tokens;
	t_ast_cmd	*ast;
	char		*command_line;
	char		*tmp;

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
	while (true)
	{
		prompt_pwd();
		command_line = readline("➤ ");
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
		// printf("\n");
		if (*command_line)
			add_history(command_line);
		free_ast(ast);
		free(command_line);
	}
	free(command_line);
	exit(g_exit_status);
}
