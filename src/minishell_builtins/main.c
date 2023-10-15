/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:24:47 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/12 18:31:30 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "builtins.h"
#include <string.h>
#include <stdlib.h>
#include <libft.h>
#include "global_utils.h"

int	main(int argc, char *argv[], char **envp)
{
	char	*command_ptr;
	char	command[100];
	char	**args;
	char	**tmp;
	size_t	size;
	char	*tmp_pwd;

	(void)argv;
	(void)argc;
	create_env(envp);
	tmp_pwd = getcwd(NULL, 0);
	pwd_trolling(tmp_pwd);
	free(tmp_pwd);
	while (1)
	{
		size = 0;
		command_ptr = NULL;
		args = NULL;
		printf("$ ");
		fflush(stdout);
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = 0;
		if (!strlen(command))
			continue ;
		args = ft_split(command, ' ');
		if (!args)
			continue ;
		command_ptr = args[0];
		tmp = &args[1];
		while (*tmp++)
			size++;
		check_builtins(size, command_ptr, &args[1]);
		memset(command, 0, sizeof(command));
		free_list(args);
	}
}
