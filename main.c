#include "include/structs.h"
#include "include/lexer.h"
#define ORANGE "\033[91m"
#define NOCOL "\033[0m"

int main(void)
{
	char *cwd = malloc(50);
	char *command_line;
	cwd = getcwd(cwd, 50);
	while (1)
	{
		printf(ORANGE"%s"NOCOL, cwd);
		command_line = readline(" > ");
		if (!command_line) break;
		lexer(command_line);
		free(command_line);
	}
	free(command_line);
	free(cwd);
}
