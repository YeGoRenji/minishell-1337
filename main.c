#include "include/structs.h"
#include "include/lexer.h"
#include "include/parser.h"
#define RED "\033[91m"
#define NOCOL "\033[0m"

int main(void)
{
	// TODO : Make an actual Prompt with PWD
	t_token	*tokens;
	char *cwd;
	char *command_line;

	cwd = getcwd(NULL, 0);
	while (1)
	{
		tokens = NULL;
		printf("["RED"%s"NOCOL"]\n", cwd);
		command_line = readline("➤ ");
		if (!command_line)
			break ; // TODO: Print exit\n
		if (lexer(command_line, &tokens))
			parser(tokens, command_line);
		add_history(command_line);
		free(command_line);
	}
	free(command_line);
	free(cwd);
}
