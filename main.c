#include "include/structs.h"
#include "include/lexer.h"
#define RED "\033[91m"
#define NOCOL "\033[0m"

int main(void)
{
	// TODO : Make an actual Prompt with PWD
	// Allocate an actual real size
	t_list	*tokens;
	char *cwd = malloc(50);
	char *command_line;

	cwd = getcwd(cwd, 50);
	while (1)
	{
		printf("["RED"%s"NOCOL"]\n", cwd);
		command_line = readline("➤ ");
		if (!command_line)
			break;
		if (!lexer(command_line, &tokens))
			break ;
		add_history(command_line);
		free(command_line);
	}
	free(command_line);
	free(cwd);
}
