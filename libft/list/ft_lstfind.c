/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:52:23 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 03:52:24 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list **ft_lstfind(t_list **lst,const char *needle, size_t size)
{
    t_list **ptr;

    ptr = lst;
    if (!needle || !size)
        return(NULL);
    while (*ptr)
    {
        if((*ptr)->content_size >= size && !ft_memcmp((*ptr)->content, needle, size))
            return(ptr);
        ptr = &(*ptr)->next;
    }
    return (NULL);
}