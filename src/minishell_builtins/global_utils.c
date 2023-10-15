/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:06:46 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 14:13:18 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

t_env	*search_in_env(t_env *env, char *key)
{
	t_env	*ptr;

	if (!env || !key)
		return (NULL);
	ptr = env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, key))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

t_env	**get_envp_internal(t_env *envp)
{
	static t_env	*env;

	if (envp)
		env = envp;
	return (&env);
}

t_env	*get_envp(t_env *envp)
{
	if (envp)
		get_envp_internal(envp);
	return (*get_envp_internal(NULL));
}

char	**consume_env(t_env *env)
{
	size_t	i;
	char	**ptr;
	size_t	size;
	t_env	*node;
	char	*tmp;

	if (!env)
		return (NULL);
	size = ft_lstsize(env);
	ptr = (char **)malloc((size + 1) * sizeof(char *));
	node = env;
	i = 0;
	while (i < size)
	{
		tmp = ft_strjoin(node->key, "=");
		// TODO: protect this
		ptr[i++] = ft_strjoin(tmp, node->value);
		free(tmp);
		node = node->next;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*get_env_value(char *var)
{
	char	*value;
	t_env	*node;

	node = search_in_env(get_envp(NULL), var + 1);
	free(var);
	if (!node)
		return (ft_strdup(""));
	value = node->value;
	return (ft_strdup(value));
}

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
		ptr = ft_lstnew(get_key(*envp), get_value(*envp), !!ft_strchr(*envp, '='), prev);
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

// TODO : might move this function to a more specific file!!
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
		edit_env(node, value, equal_sign);
		free(key);
	}
}
