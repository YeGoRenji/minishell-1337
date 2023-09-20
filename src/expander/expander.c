/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:42:37 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/20 01:57:37 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

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
		while (ft_isalnum(ptr[len]) || ptr[len] == '_')
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

void	add_str_lst(char *str, t_str **lst, bool join_to_last, t_token *tok)
{
	bool to_expand;

	to_expand = (tok->type == WORD && ft_strchr(str, '*'));

	if (tok->type == WORD && !ft_strncmp(str, "$", 2) && tok->nospace_next)
		str = "";
	if (join_to_last)
		ft_join_last(lst, str, to_expand);
	else
		ft_stradd_back(lst, new_str(str, to_expand));
}

void	expand_nosp_arg(t_token *sub_tok, t_str **lst)
{
	// TODO : maybe handle wildcards
	char			*to_join;
	char			**splited;
	int				i;
	int				iter;

	iter = 0;
	while (sub_tok)
	{
		to_join = expand(sub_tok);
		// printf("expand_nosp_arg > Got <%s> \n", to_join);
		if (ft_strchr(to_join, TROLL))
		{
			splited = ft_split(to_join, TROLL);
			i = 0;
			while (splited[i])
			{
				add_str_lst(splited[i], lst, i == 0 && iter != 0, sub_tok);
				i++;
			}
			(free_list(splited), splited = NULL);
		}
		else
			add_str_lst(to_join, lst, iter != 0, sub_tok);
		sub_tok = sub_tok->nospace_next;
		(free(to_join), iter++);
	}
}

char	**expand_args(t_token *tok_lst)
{
	// TODO : maybe return t_str and consume outside after wildcard !
	char	**argv;
	t_str	*argv_lst;

	argv_lst = NULL;
	while (tok_lst)
	{
		expand_nosp_arg(tok_lst, &argv_lst);
		// printf("expand_args > Got <%s> \n", argv[i - 1]);
		tok_lst = tok_lst->next;
	}
	// ft_striter(argv_lst, p_str_node); // ? Debug
	argv = consume_argv(argv_lst);
	// int i = 0;
	// printf("--uwu---\n"); // ? Debug
	// while (argv[i])
	// 	printf("%s\n", argv[i++]);
	// printf("--------\n");
	return (argv);
}
