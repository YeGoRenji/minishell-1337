/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:59:24 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/29 15:00:17 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stringbuilder.h>

static size_t	align(size_t size)
{
	return ((size + (16 - 1)) & ~ (16 - 1));
}

void	sb_reallocate(t_strbuilder *sb, size_t len)
{
	char	*new;

	sb->capacity = align(sb->used_len + len + 1);
	new = ft_calloc(1, sb->capacity);
	ft_memcpy(new, sb->str, sb->used_len);
	free(sb->str);
	sb->str = new;
}
