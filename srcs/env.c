/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:01 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/23 00:52:02 by aait-ihi         ###   ########.fr       */
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

void ft_env(t_list **env, char **cmd)
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
                ft_shellmain(cmd + i, dup);
                break;
            }
        }
        if (!cmd[i])
            (ft_display_env(dup));
    }
}

t_list *get_env_var(char *str, t_env_var *var)
{
    if(ft_strequ(str,"HOME"))
        return(var->home);
    if(ft_strequ(str,"PWD"))
        return(var->pwd);
    if(ft_strequ(str,"OLDPWD"))
        return(var->oldpwd);
    if(ft_strequ(str,"PATH"))
        return(var->path);
    return (NULL);
}

void ft_setenvcases(char **cmd, t_list **env, t_env_var *var)
{
    char *newenv;
    t_list *new;
    t_list **to_modify;

    newenv = NULL;
    if ((newenv = ft_strnjoin((char *[]){cmd[1], "=", cmd[2]}, 3)))
    {
        if ((to_modify = ft_lstfind(env, cmd[1], ft_strlen(cmd[1]) + 1)))
        {
            ft_lstmodifone(*to_modify, newenv);
            ft_strreplace((*to_modify)->content, '=', 0);
        }
        else if ((new = get_env_var(cmd[1], var)))
        {
            ft_lstmodifone(new, newenv);
            ft_strreplace(new->content, '=', 0);
            ft_lstadd(env, new);
        }
        else
        {
            if ((new = ft_lstpushback(env, newenv, ft_strlen(newenv) + 1)))
                ft_strreplace((new)->content, '=', 0);
            free(newenv);
        }
    }
}

void ft_setenv(char **cmd, t_list **env, t_env_var *var)
{
    if (cmd[3])
        return (ft_print_error(cmd[0], ERR_MNARGS, 0));
    if (!cmd[1])
        return (ft_display_env(*env));
    if (!ft_isalpha(cmd[1][0]))
        return (ft_print_error(cmd[0], ERR_FSTLTR, 0));
    if (!ft_strisalnum(cmd[1]))
        return (ft_print_error(cmd[0], ERR_ALFA, 0));
    ft_setenvcases(cmd, env, var);
}
