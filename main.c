#include <structs.h>
#include <lexer.h>
#include <parser.h>
#define RED "\033[91m"
#define NOCOL "\033[0m"

void chk(void)
{
	system("leaks minishell");
}

int main(void)
{
	// TODO : Make an actual Prompt with PWD
	t_token		*tokens;
	t_ast_cmd	*ast;
	char		*cwd;
	char		*command_line;

	atexit(chk); // ? Debug

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
		if (lexer(command_line, &tokens))
			parser(tokens, command_line, &ast);
		if (*command_line)
			add_history(command_line);
		free_ast(ast);
		free(command_line);
	}
	free(command_line);
	free(cwd);
}
