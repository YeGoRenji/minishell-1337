/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:25:42 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/17 14:48:29 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

char	*ft_chr(char *str, char c)
{
	return (ft_strchr(str, c));
}

char	*expand_env(char *to_expand, bool in_quote, bool ignore_env)
{
	char			*ptr;
	size_t			len;
	t_strbuilder	*sb;
	char			*chunk;

	sb = stringbuilder();
	ptr = to_expand;
	while (*ptr)
	{
		len = get_chunk_len(ptr, "$");
		chunk = ft_substr(ptr, 0, len);
		if (!ignore_env && *ptr == '$' && len > 1)
		{
			if (len == 2 && ptr[1] == '?')
				(free(chunk), chunk = ft_itoa(get_exit_status()));
			else
			{
				chunk = get_env_value(chunk);
				if (!in_quote && (ft_chr(chunk, ' ') || ft_chr(chunk, '\t')))
					ghost_char_trolling(chunk);
			}
		}
		(sb_append_free(sb, chunk), ptr += len);
	}
	return (free(to_expand), to_expand = sb->str, free(sb), to_expand);
}

char	*expand(t_token *tok, bool ignore_env)
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
	if (!ignore_env && str)
		str = expand_env(str, tok->type == DQSTR, ignore_env);
	return (str);
}

void	expand_nosp_arg(t_token *sub_tok, t_str **lst, bool ignore_env)
{
	char			*to_join;
	char			**splited;
	int				i;
	int				iter;

	iter = 0;
	while (sub_tok)
	{
		to_join = expand(sub_tok, ignore_env);
		if (ft_strchr(to_join, TROLL))
		{
			splited = ft_split(to_join, (char )TROLL);
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
	char	**argv;
	t_str	*argv_lst;

	argv_lst = NULL;
	while (tok_lst)
	{
		expand_nosp_arg(tok_lst, &argv_lst, 0);
		tok_lst = tok_lst->next;
	}
	argv_lst = expand_wild_cards(argv_lst);
	argv = consume_argv(argv_lst);
	return (argv);
}
