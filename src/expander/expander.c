/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:42:37 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/15 01:24:56 by ylyoussf         ###   ########.fr       */
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

char	*expand_special(char *to_expand, char *specials)
{
	char			*ptr;
	size_t			len;
	t_strbuilder	*sb;
	char			*chunk;

	if (!to_expand)
		return (NULL);
	sb = stringbuilder();
	ptr = (char *)to_expand;
	while (*ptr)
	{
		len = get_chunk_len(ptr, specials);
		chunk = ft_substr(ptr, 0, len);
		if (*ptr == '$' && len > 1)
		{
			if (len == 2 && ptr[1] == '?')
				(free(chunk), chunk = ft_itoa(g_exit_status));
			else
				chunk = get_env_value(chunk);
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
	char	*specials;

	specials = "$";
	// TODO : maybe handle wildcards
	if (tok->type == DQSTR)
	{
		str = ft_strtrim(tok->value, "\"");
		specials = "$";
	}
	else if (tok->type == STR)
		str = ft_strtrim(tok->value, "'");
	else
		str = ft_strdup(tok->value);
	if (!tok->to_expand)
		return (str);
	str = expand_special(str, specials);
	return (str);
}

char	*expand_nosp_arg(t_token *argv_tok)
{
	char			*to_join;
	t_strbuilder	*sb;
	char			*to_return;

	sb = stringbuilder();
	while (argv_tok)
	{
		to_join = expand(argv_tok);
		sb_append_free(sb, to_join);
		argv_tok = argv_tok->nospace_next;
	}
	to_return = sb->str;
	free(sb);
	return (to_return);
}

char	**expand_args(t_token *argv_tok)
{
	int		i;
	char	**argv;

	argv = ft_calloc(tok_lst_len(argv_tok) + 1, sizeof(char *));
	i = 0;
	while (argv_tok)
	{
		argv[i++] = expand_nosp_arg(argv_tok);
		// printf("expand_args > Got <%s> \n", argv[i - 1]);
		argv_tok = argv_tok->next;
	}
	return (argv);
}
