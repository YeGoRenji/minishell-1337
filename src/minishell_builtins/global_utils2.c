/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:30:26 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/17 16:53:28 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

void	create_env(char **envp)
{
	t_env	**env;
	t_env	*prev;
	t_env	*ptr;

	if (!envp)
		return ;
	env = get_envp_internal(NULL);
	prev = NULL;
	while (*envp)
	{
		ptr = ft_lstnew(get_key(*envp), get_value(*envp),
				!!ft_strchr(*envp, '='), prev);
		ft_lstadd_back(env, ptr);
		prev = ptr;
		envp++;
	}
}

void	log_last_command(char *value)
{
	if (!value)
		return ;
	set_env_value(ft_strdup("_"), ft_strdup(value), 1);
}

char	*get_key(char *line)
{
	size_t	index;
	char	*equal_sign;

	if (!line)
		return (NULL);
	equal_sign = ft_strchr(line, '=');
	if (equal_sign)
	{
		index = (size_t)equal_sign - (size_t)line;
		if (is_concate(line))
			index--;
		return (ft_substr(line, 0, index));
	}
	return (ft_strdup(line));
}

char	*get_value(char *line)
{
	char	*equal_sign;

	if (!line)
		return (NULL);
	equal_sign = ft_strchr(line, '=');
	if (!equal_sign)
		return (ft_strdup(""));
	return (ft_substr(equal_sign, 1, ft_strlen(equal_sign + 1)));
}

void	set_env_value(char *key, char *value, int equal_sign)
{
	t_env	**env;
	t_env	*node;

	if (!key || !value)
		return ;
	env = get_envp_internal(NULL);
	node = search_in_env(*env, key);
	if (!node)
		append_to_env(env, key, value, equal_sign);
	else
	{
		edit_env(node, value, 1);
		free(key);
	}
}
