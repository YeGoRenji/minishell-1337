/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 03:17:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/24 15:05:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"
# include "structs.h"

void	syntax_error(char *where);
void	tok_error(char which);
void	unclosed_error(char which);

#endif // ERROR_H
