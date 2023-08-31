/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:50:41 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/31 17:55:23 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"
#include "builtins.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	echo(int argc, char **args)
{
	int		new_line;
	int		i;
	char	*option;

	if (!args)
		return (ft_putstr_fd("\n", 1));
	i = 0;
	new_line = 1;
	while (i <= argc - 1)
	{
		option = args[i];
		if (option && ft_strlen(option + 1) && consists_of(option + 1, 'n'))
		{
			new_line = 0;
			i++;
		}
		else
			break ;
	}
	while (i < argc - 1)
	{
		ft_putstr_fd(args[i++], 1);
		ft_putstr_fd(" ", 1);
	}
	if (i <= argc - 1)
		ft_putstr_fd(args[i++], 1);
	if (new_line)
		ft_putstr_fd("\n", 1);
}

void	cd(int argc, char *arg)
{
	char	*home_dir;

	if (argc && !arg)
		return ;
	home_dir = getenv("HOME");
	// TODO : check if MAC's gentev has the extension that allocates the buffer
	// in the heap just like linux
	if (!argc)
	{
		if (!home_dir)
			return (ft_putstr_fd("cd: HOME not set\n", 2));
		//		return (ft_putstr_fd("cd: HOME not set\n", 2),
		//				free(home_dir));
		// TODO : test this when u make pwd!!!
		else if (chdir(home_dir) == -1)
			perror("chdir");
	}
	else
	{
		if (arg[0] == '/')
		{
			if (chdir(arg) == -1)
				perror("chdir");
		}
		else
		{
			;
			// TODO make a path depending on if args is relative or absolute
		}
	}
	// free(cur_dir); ?
	// TODO : change PWD in env
}

void	pwd()
{
	char 		*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
		pwd_trolling(tmp);
	printf("%s\n", pwd_trolling(NULL));
}

void	env_(t_env **env)
{
	return (print_env(*env));
}
void	export(int argc, char **argv, t_env **env)
{
	int		i;
	char	*ptr;
	char	**tmp;
	t_env	*tmp_node;

	if (!env)
		return ;
	if (!argc)
		return (print_exports(*env));
	i = 0;
	while (i < argc)
	{
		ptr = argv[i++];
		if (validate_var_name(ptr))
		{
			printf("export: `%s': not a valid identifier\n", ptr);
			continue ;
		}
		tmp = ft_split(ptr, '=');
		if (!tmp)
			continue ;
		tmp_node = search_in_env(*env, tmp[0]);
		if (!tmp_node)
			append_to_env(env, ptr);
		else
			edit_env(tmp_node, tmp[1]);
		free_list(tmp);
	}
}

void	unset(int argc, char **args, t_env **env)
{
	char	*ptr;
	int		i;

	if (!args || !env)
		return ;
	i = 0;
	while (i < argc)
	{
		ptr = args[i++];
		if (ft_isdigit(*ptr))
		{
			printf("unset: `%s': not a valid identifier\n", ptr);
			continue ;
		}
		del_from_env(env, ptr);
	}
}

void	my_exit(char *arg)
{
	exit(ft_atoi(arg));
}
