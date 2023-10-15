/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:34:07 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 13:41:42 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd_utils.h"

int	pwd(void)
{
	printf("%s\n", pwd_trolling(NULL));
	return (0);
}
