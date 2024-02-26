/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:58:33 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/26 21:36:41 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGBUILDER_H
# define STRINGBUILDER_H

# include "libft.h"

typedef struct s_stringbuilder
{
	size_t	capacity;
	size_t	used_len;
	char	*str;
}	t_strbuilder;

void			sb_reallocate(t_strbuilder *sb, size_t len);
t_strbuilder	*stringbuilder(void);
t_strbuilder	*sb_append(t_strbuilder *sb, char *str);
t_strbuilder	*sb_append_free(t_strbuilder *sb, char *str);
t_strbuilder	*sb_append_int(t_strbuilder *sb, int nb);
void			sb_free(t_strbuilder *sb);

#endif
