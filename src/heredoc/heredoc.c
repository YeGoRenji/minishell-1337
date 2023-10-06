/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:02:14 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/06 15:08:11 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

char	*handle_heredoc(char *delim)
{
	char	*line;
	char	*tmp_file;
	int		fd;

	if (!delim)
		return (NULL);
	tmp_file = ft_mktmp();
	puts(tmp_file);
	fd = open(tmp_file, O_RDWR | O_CREAT, 0640);
	if (fd < 0)
	{
		perror("open");
		return (NULL);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			return (NULL);
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(delim, line, ft_strlen(delim) + 1))
			break ;
		line = expand_env(line, false);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	return (tmp_file);
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

void patch_heredoc(t_ast_cmd *tree)
{
	int type;
	if (!tree)
		return ;
	type = tree -> type;
	if (type == P_AND || type == P_OR || type == P_PIPE)
	{
		patch_heredoc(((t_ast_binary *)tree) -> left);
		patch_heredoc(((t_ast_binary *)tree) -> right);
	}
	else if (tree->type == P_SUBSH)
		patch_heredoc(((t_ast_subsh *)tree) -> cmd);
	else if (tree->type == P_REDIR && ((t_ast_redir *)tree) -> direction == HEREDOC)
	{
		patch_token((t_ast_redir *)tree);
		patch_heredoc(((t_ast_redir *)tree) -> cmd);
	}

}

void patch_token(t_ast_redir *tree)
{
	t_token *tok;
	if (!tree)
		return;
	tok = tree -> file_tok;
	tree -> direction = INPUT;
	tok -> type = INPUT;
	tok -> value = handle_heredoc(tree -> file_tok -> value);
	tok -> to_expand = false;
}
