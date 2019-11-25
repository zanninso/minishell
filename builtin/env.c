/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:01 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 23:48:17 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_display_env(t_list *env)
{
    while (env)
    {
        ft_strreplace(env->content, 0, '=');
        ft_putendl(env->content);
        ft_strreplace(env->content, '=', 0);
        env = env->next;
    }
}

void ft_env_args(char *cmd, t_list **dup)
{
    int len;
    t_list **to_mod;
    t_list *new;

    len = ft_strlen(cmd);
    ft_strreplace(cmd, '=', 0);
    if ((to_mod = ft_lstfind(dup, cmd, ft_strlen(cmd) + 1)))
    {
        ft_strreplace(cmd, 0, '=');
        ft_lstmodifone(*to_mod, cmd);
        ft_strreplace((*to_mod)->content, '=', 0);
    }
    else if ((new = ft_lstpushback(dup, cmd, len + 1)))
        ft_strreplace((new)->content, '=', 0);
}

void ft_env(t_list **env, char **cmd, t_env_var *var)
{
    t_list *dup;
    int i;

    if (!cmd[1] && env)
        return (ft_display_env(*env));
    if ((dup = ft_lstdup(env)))
    {
        i = 0;
        while (cmd[++i])
        {
            if (ft_strchr(cmd[i], '='))
                ft_env_args(cmd[i], &dup);
            else
            {
                ft_shellmain(cmd + i, dup, var);
                break;
            }
        }
        if (!cmd[i])
            (ft_display_env(dup));
    }
}
