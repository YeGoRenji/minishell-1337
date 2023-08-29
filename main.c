/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:53:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/29 21:42:20 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globals.h>
#include <lexer.h>
#include <parser.h>
#include <executor.h>

#define RED "\033[91m"
#define NOCOL "\033[0m"

void chk(void)
{
	// system("leaks minishell");
}

int	g_exit_status;

int main(void)
{
	// TODO : Make an actual Prompt with PWD
	t_token		*tokens;
	t_ast_cmd	*ast;
	char		*cwd;
	char		*command_line;

	// atexit(chk); // ? Debug
	cwd = getcwd(NULL, 0);
	while (true)
	{
		printf("["RED"%s"NOCOL"]\n", cwd);
		command_line = readline("➤ ");
		if (!command_line)
		{
			ft_putendl_fd("\nexit", 1);
			break ;
		}
		lexer(command_line, &tokens);
		parser(tokens, command_line, &ast);
		printf("----- EXECUTOR ----\n");
		executor(ast);
		// printf("\n");
		if (*command_line)
			add_history(command_line);
		free_ast(ast);
		free(command_line);
	}
	free(command_line);
	free(cwd);
}
