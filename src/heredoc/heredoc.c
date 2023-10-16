/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:02:14 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 19:40:50 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

char	*handle_heredoc(char *delim, bool expandable)
{
	char	*line;
	char	*tmp_file;
	int		fd;

	if (!delim)
		return (NULL);
	tmp_file = ft_mktmp();
	fd = open(tmp_file, O_RDWR | O_CREAT, 0640);
	if (fd < 0)
		return (print_err(tmp_file, 0), set_exit_status(1), NULL);
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			return (close(fd), tmp_file);
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(delim, line, ft_strlen(delim) + 1))
			break ;
		line = expand_env(line, false, !expandable);
		(ft_putendl_fd(line, fd), free(line));
	}
	free(line);
	return (close(fd), tmp_file);
}

char	*ft_mktmp(void)
{
	t_strbuilder	*sb;
	char			*name;
	int				i;

	i = 0;
	while (++i)
	{
		sb = stringbuilder();
		sb_append(sb, "/tmp/SHELL69_HEREDOC_");
		sb_append_int(sb, i);
		name = ft_strdup(sb->str);
		sb_free(sb);
		if (access(name, F_OK))
			break ;
		free(name);
	}
	return (name);
}

int	patch_heredoc(t_ast_cmd *tree)
{
	int	type;

	if (!tree)
		return (0);
	type = tree->type;
	if (type == P_AND || type == P_OR || type == P_PIPE)
	{
		patch_heredoc(((t_ast_binary *)tree)->left);
		patch_heredoc(((t_ast_binary *)tree)->right);
	}
	else if (tree->type == P_SUBSH)
		patch_heredoc(((t_ast_subsh *)tree)->cmd);
	else if (tree->type == P_REDIR)
	{
		if (((t_ast_redir *)tree)->direction == HEREDOC)
			patch_token((t_ast_redir *)tree);
		patch_heredoc(((t_ast_redir *)tree)->cmd);
	}
	return (g_last_signal != 420);
}

void	patch_token(t_ast_redir *tree)
{
	t_token	*tok;
	t_str	*s_ptr;

	if (!tree)
		return ;
	s_ptr = NULL;
	tok = NULL;
	expand_nosp_arg(tree->file_tok, &s_ptr, 1);
	tok = tree->file_tok;
	free(tok->value);
	tok->value = handle_heredoc(s_ptr->str, is_expandable(tree -> file_tok));
	signal(SIGINT, sigint_handler);
	tok->len = 0;
	if (tok->value)
		tok->len = ft_strlen(tok->value);
	tree->direction = INPUT;
	free_tok_lst(tok->nospace_next);
	tok->nospace_next = NULL;
	free(s_ptr->str);
	free(s_ptr);
	tok->to_expand = false;
}

bool	is_expandable(t_token *tok)
{
	t_token	*ptr;

	if (!tok)
		return (1);
	ptr = tok;
	while (ptr)
	{
		if (ptr->type == DQSTR || ptr->type == STR)
			return (0);
		ptr = ptr->nospace_next;
	}
	return (1);
}
