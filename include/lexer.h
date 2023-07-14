/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 02:01:47 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/14 21:18:33 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

// TODO : Add dollar token
// TODO : Add wildcard token ?
typedef enum e_token_type {
	WORD = 0,
	STR,
	DQSTR,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
	LPREN,
	RPREN,
	PIPE,
	OR,
	AND
} t_token_type;

int lexer(char *command_line);

#endif // LEXER_H
