/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:56:55 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/23 13:37:31 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <assert.h>

t_str	*new_str(char *str, bool to_expand)
{
	t_str	*node;

	node = malloc(sizeof(t_str));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->wild_card = to_expand;
	node->next = NULL;
	return (node);
}

t_str	*ft_strlast(t_str *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_stradd_back(t_str **lst, t_str *new)
{
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ft_strlast(*lst)->next = new;
}

void	free_strnode(t_str *node)
{
	free(node->str);
	free(node);
}

void	p_str_node(void *s)
{
	t_str	*sot = s;

	fprintf(stderr, "[%s] wild_card: %s\n", sot->str, sot->wild_card ? "true" : "false");
}

int	ft_strlstlen(t_str *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	ft_striter(t_str *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}

void	ft_join_last(t_str **lst, char *str, bool to_expand)
{
	char	*joined;
	t_str	*str_last;
	bool	old_to_expand;

	str_last = ft_strlast(*lst);
	if (!str_last)
		return (ft_stradd_back(lst, new_str(str, to_expand)));
	joined = ft_strjoin(str_last->str, str);
	old_to_expand = str_last->wild_card;
	free(str_last->str);
	str_last->str = joined;
	str_last->wild_card = old_to_expand || to_expand;
}

int	split_len(char **lst)
{
	int	len;

	len = 0;
	while (lst[len])
		len++;
	return (len);
}

char	**consume_argv(t_str *lst)
{
	char	**argv;
	t_str	*tmp;
	int		i;
	int		len;

	len = ft_strlstlen(lst);
	argv = malloc((len + 1) * sizeof(char *));

	i = 0;
	while (i < len)
	{
		argv[i++] = lst->str;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	argv[i] = NULL;
	return (argv);
}
