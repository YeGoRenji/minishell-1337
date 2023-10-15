/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 03:17:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/15 14:54:55 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include "stringbuilder.h"
# include "hacks.h"


void	syntax_error(char *where);
void	tok_error(char which);
void	unclosed_error(char which);
int		print_err(char *preced, int msg_code);

#endif // ERROR_H
