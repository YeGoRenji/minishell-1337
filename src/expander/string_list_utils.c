/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:58:09 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/11 17:11:02 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

int	split_len(char **lst)
{
	int	len;

	len = 0;
	while (lst[len])
		len++;
	return (len);
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

void	add_str_lst(char *str, t_str **lst, bool join_to_last, t_token *tok)
{
	bool	to_expand;

	to_expand = (tok->type == WORD && ft_strchr(str, '*'));
	if (tok->type == WORD && !ft_strncmp(str, "$", 2) && tok->nospace_next)
		str = "";
	if (join_to_last)
		ft_join_last(lst, str, to_expand);
	else
		ft_stradd_back(lst, new_str(str, to_expand));
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
