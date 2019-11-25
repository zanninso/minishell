/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:48:22 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 23:48:40 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    if (!ft_str_match(cmd[1], ft_isalnum))
        return (ft_print_error(cmd[0], ERR_ALFA, 0));
    ft_setenvcases(cmd, env, var);
}