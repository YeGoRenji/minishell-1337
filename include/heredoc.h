/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:03:53 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/06 18:19:00 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include <ast.h>
# include <expander.h>
# include <globals.h>
# include <stringbuilder.h>
char	*handle_heredoc(char *delim, bool expand_env);
char	*ft_mktmp(void);
void	patch_heredoc(t_ast_cmd *tree);
void	patch_token(t_ast_redir *tree);
bool	is_expandable(t_token *tok);
#endif
