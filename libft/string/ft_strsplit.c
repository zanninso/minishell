/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:03:34 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 05:01:59 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define TR(c,v) ((c) >= 0 ? (c) : (v))

char	**ft_strsplit(char const *s, char c)
{
	int		size;
	int		i;
	char	**tab2d;
	char cmp[2];

	cmp[0] = c;
	cmp[1] ='\0'; 
	if (!s)
		return (0);
	i = 0;
	size = ft_wordcount(s, c);
	if (!(tab2d = (char **)malloc((size + 1) * sizeof(char *))))
		return (0);
	while (size--)
	{
		s = ft_skipchr(s, c);
		tab2d[i + 1] = (char *)ft_skip_unitl_char(s, cmp);
		tab2d[i] = ft_strsub(s, 0, tab2d[i + 1] - s);
		s = tab2d[i + 1];
		i++;
	}
	tab2d[i] = 0;
	return (tab2d);
}
