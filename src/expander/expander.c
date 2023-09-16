/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:42:37 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/16 04:26:24 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

int	tok_lst_len(t_token *tok_lst)
{
	int	len;

	len = 0;
	while (tok_lst)
	{
		len++;
		tok_lst = tok_lst->next;
	}
	return (len);
}

bool	in_set(char *set, char c)
{
	while (*set)
		if (*set++ == c)
			return (true);
	return (false);
}

unsigned int	get_chunk_len(char *ptr, char *sp)
{
	unsigned int	len;

	len = 0;
	if (!in_set(sp, *ptr))
	{
		while (ptr[len] && !in_set(sp, ptr[len]))
			len++;
	}
	else
	{
		len++;
		if (ptr[1] == '?')
			return (len + 1);
		while (ft_isalnum(ptr[len]))
			len++;
	}
	return (len);
}

void	ghost_char_trolling(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = TROLL;
		i++;
	}
}

char	*expand_env(char *to_expand, bool in_quote)
{
	char			*ptr;
	size_t			len;
	t_strbuilder	*sb;
	char			*chunk;

	if (!to_expand)
		return (NULL);
	sb = stringbuilder();
	ptr = to_expand;
	while (*ptr)
	{
		len = get_chunk_len(ptr, "$");
		chunk = ft_substr(ptr, 0, len);
		// printf("big_chunk = <%s>\n", chunk);
		if (*ptr == '$' && len > 1)
		{
			if (len == 2 && ptr[1] == '?')
				(free(chunk), chunk = ft_itoa(g_exit_status));
			else
			{
				chunk = get_env_value(chunk);
				if (!in_quote && ft_strchr(chunk, ' '))
					ghost_char_trolling(chunk);
			}
		}
		sb_append_free(sb, chunk);
		ptr += len;
	}
	free(to_expand);
	to_expand = sb->str;
	free(sb);
	return (to_expand);
}

char	*expand(t_token *tok)
{
	char	*str;

	if (tok->type == DQSTR)
		str = ft_strtrim(tok->value, "\"");
	else if (tok->type == STR)
		str = ft_strtrim(tok->value, "'");
	else
		str = ft_strdup(tok->value);
	if (!tok->to_expand)
		return (str);
	str = expand_env(str, tok->type == DQSTR);
	return (str);
}

char	*expand_nosp_arg(t_token *argv_tok, t_str **lst)
{
	// TODO : maybe handle wildcards
	char			*to_join;
	t_strbuilder	*sb;
	char			*to_return;
	char			**splited;
	int				i;
	int				iter;

	sb = stringbuilder();
	iter = 0;
	while (argv_tok)
	{
		to_join = expand(argv_tok);
		// printf("expand_nosp_arg > Got <%s> \n", to_join);
		if (ft_strchr(to_join, TROLL))
		{
			splited = ft_split(to_join, TROLL);
			i = 0;
			while (splited[i])
			{
				if (i == 0 && iter != 0)
					ft_join_last(lst, splited[i]);
				else
					ft_stradd_back(lst, new_str(splited[i], ft_strchr(splited[i], '*')));
				i++;
			}
			(free_list(splited), splited = NULL);
		}
		else if (!iter)
			ft_stradd_back(lst, new_str(to_join, ft_strchr(to_join, '*')));
		else
			ft_join_last(lst, to_join);
		sb_append_free(sb, to_join);
		argv_tok = argv_tok->nospace_next;
		iter++;
	}
	to_return = sb->str;
	free(sb);
	return (to_return);
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

char	**expand_args(t_token *tok_lst)
{
	int		i;
	char	**argv;
	char	**uwu_argv;
	t_str	*argv_lst;
	// TODO : use a list instead
	// TODO : use uwu_argv instead of argv

	argv = ft_calloc(tok_lst_len(tok_lst) + 1, sizeof(char *));
	argv_lst = NULL;
	i = 0;
	while (tok_lst)
	{
		argv[i++] = expand_nosp_arg(tok_lst, &argv_lst);
		// printf("expand_args > Got <%s> \n", argv[i - 1]);
		tok_lst = tok_lst->next;
	}
	// ft_striter(argv_lst, p_str_node); // ? Debug
	uwu_argv = consume_argv(argv_lst);
	i = 0;
	free_list(argv);
	// printf("--uwu---\n"); // ? Debug
	// while (argv[i])
	// 	printf("%s\n", argv[i++]);
	// printf("--------\n");
	return (uwu_argv);
}
