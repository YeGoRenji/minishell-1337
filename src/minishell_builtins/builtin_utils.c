/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:49:12 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 14:03:08 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"
#include "lst_operations.h"
#include <libft.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // TODO : use libft's instead
#include <unistd.h>

void	log_last_command(char *value)
{
	char	*arr[2];

	if (!value)
		return ;
	arr[0] = ft_strjoin("_=", value);
	arr[1] = 0;
	export(1, arr, get_envp_internal(NULL));
}
