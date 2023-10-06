/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:33:51 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/06 14:38:12 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "lexer.h"
# include "error.h"
# include "heredoc.h"

bool	parser(t_token *tokens, char *cmd, t_ast_cmd **tree);

#endif // PARSER_H
