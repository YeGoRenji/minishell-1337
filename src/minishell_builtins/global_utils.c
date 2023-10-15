/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:06:46 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 17:31:45 by ylyoussf         ###   ########.fr       */
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
	ptr = (char **)ft_malloc((size + 1) * sizeof(char *));
	node = env;
	i = 0;
	while (i < size)
	{
		tmp = ft_strjoin(node->key, "=");
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
