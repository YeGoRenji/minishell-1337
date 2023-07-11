#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline/readline.h"

int main(void)
{
	char *path = malloc(50);
	int fd[2];
	while (69)
	{
		printf("%s", path);
		char *lol = readline(" > ");
		pipe(fd);
		if (!fork())
		{
			close(fd[0]);
			write(fd[1], "69 lol", 6);
			system(lol);
		}
		else
		{
			close(fd[1]);
			int bytes_read = read(fd[0], path, 50);
			wait(NULL);
		}
	}
}
