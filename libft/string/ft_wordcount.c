/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:23:21 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 04:52:59 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(const char *s, char c)
{
	int	size;
	char cmp[2];

	cmp[0] = c;
	cmp[1] = '\0';
	size = 0;
	while (*s)
	{
		size += *s && *s != c ? 1 : 0;
		s = ft_skip_unitl_char(s, cmp);
		s = ft_skipchr(s, c);
	}
	return (size);
}
