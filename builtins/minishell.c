#include "builtin_utils.h"
#include "builtins.h"
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h> // TODO : add clone the libft that has ft_strcmp

int	main(int argc, char *argv[], char **envp)
{
	char	*command_ptr;
	char	command[100];
	char	**args;
	char	**tmp;
	size_t	size;
	t_env	*env;

	(void)argv;
	(void)argc;
	env = create_env(envp);
	pwd_trolling(getcwd(NULL, 0));
	while (1)
	{
		size = 0;
		command_ptr = NULL;
		args = NULL;
		printf("$ ");
		fflush(stdout);
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = 0;
		if (strlen(command) == 1)
			continue ;
		args = ft_split(command, ' ');
		command_ptr = args[0];
		tmp = &args[1];
		while (*tmp++)
			size++;
		builtins(size, command_ptr, &args[1], &env);
		memset(command, 0, sizeof(command));
		free_list(args);
	}
}

void	builtins(int argc, char *command, char **args, /* char **envp,
		*/ t_env **env)
{
	if (!command /* || !envp)*/) // TODO : double check this statement
		return ;
	if (!strcmp(command, "echo")) // TODO : use libft version that has ft_strcmp
		echo(argc, args);
	//	else if (!strcmp(command, "cd"))
	//		cd(argc, *args, env);
	else if (!strcmp(command, "pwd"))
		pwd(*env);
	else if (!strcmp(command, "export"))
		// TODO : this doesn't print like bash command does
		export(argc, args, env);
	else if (!strcmp(command, "unset"))
		unset(argc, args, env);
	else if (!strcmp(command, "exit"))
		my_exit(*args);
		else if (!strcmp(command, "env"))
			env_(env);
	else
		ft_putstr_fd("command not a builtin!\n", 2);
}
