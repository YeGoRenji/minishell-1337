/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:35:10 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 13:48:54 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_utils.h"

int	print_exports(t_env *env)
{
	t_env	*ptr;

	if (!env)
		return (1);
	ptr = env;
	while (ptr)
	{
		if (ptr->equal_sign)
		{
			if (ptr->value)
				printf("declare -x %s=\"%s\"\n", ptr->key, ptr->value);
			else
				printf("declare -x %s=\"\"\n", ptr->key);
		}
		else
			printf("declare -x %s\n", ptr->key);
		ptr = ptr->next;
	}
	return (0);
}

int	is_concate(char *str)
{
	char	*concat_sign;
	char	*equal_sign;

	if (!str)
		return (false);
	equal_sign = ft_strchr(str, '=');
	concat_sign = ft_strnstr(str, "+=", ft_strlen(str));
	if (concat_sign && (size_t)concat_sign < (size_t)equal_sign)
		return (true);
	return (false);
}

void	append_to_env(t_env **env, char *key, char *value, int equal_sign)
{
	t_env	*prev;
	t_env	*node;

	if (!env || !value)
		return ;
	prev = NULL;
	if (*env)
		prev = ft_lstlast(*env);
	node = ft_lstnew(key, value, equal_sign, prev);
	ft_lstadd_back(env, node);
}

void	edit_env(t_env *node, char *value, int equal_sign)
{
	if (!node || !value)
		return ;
	free(node->value);
	node->value = value;
	node->equal_sign = equal_sign;
}

void	concate_env(char *key, char *value)
{
	t_env	*node;
	char	*old_value;

	if (!key)
		return ;
	node = search_in_env(get_envp(NULL), key);
	if (node)
	{
		free(key);
		old_value = node->value;
		node->value = ft_strjoin(old_value, value);
		node->equal_sign = 1;
		free(old_value);
		free(value);
	}
	else
	{
		node = ft_lstnew(key, value, 1, ft_lstlast(get_envp(NULL)));
		ft_lstadd_back(get_envp_internal(NULL), node);
	}
}
