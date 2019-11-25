/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:57:39 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 23:57:43 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printmatrix(char **tab)
{
    int i = -1;
    while (tab[++i])
        ft_putendl(tab[i]);
}

void printlist(t_list *env)
{
    while (env)
    {
        ft_putendl(env->content);
        env = env->next;
    }
}