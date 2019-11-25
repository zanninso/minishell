/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:44 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/24 23:26:54 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strisalnum(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isalnum(str[i]))
            return (0);
        i++;
    }
    return (1);
}

_Bool		is_dir(const char *file_name)
{
	DIR		*dirp;

	if ((dirp = opendir(file_name)))
    {
		closedir(dirp);
        return(1);
    }
    return(0);
}

