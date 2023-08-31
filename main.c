/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:53:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/31 16:09:28 by ylyoussf         ###   ########.fr       */
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

char	**get_envp(char **envp)
{
	static char	**envp_s;

	if (envp)
		envp_s = envp;
	return (envp_s);
}

int main(int _, char **__, char **envp)
{
	// TODO : Make an actual Prompt with PWD
	t_token		*tokens;
	t_ast_cmd	*ast;
	char		*cwd;
	char		*command_line;

	// atexit(chk); // ? Debug
	(void)_;
	(void)__;
	get_envp(envp);
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
	free(cwd);
}
