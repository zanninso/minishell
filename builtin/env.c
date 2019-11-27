/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:31:31 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/27 13:26:28 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_display_env(t_list *e)
{
	while (e)
	{
		ft_printf("%s=%s", e->content, e->content + ft_strlen(e->content));
		e = e->next;
	}
}

void ft_unsetenv(char **cmd, t_list **env)
{
	int i;
	t_list **del;

	i = 1;
	while (cmd[i])
	{
		if ((del = ft_lstfind(env, cmd[i], ft_strlen(cmd[i]) + 1)))
			ft_lstonedel(del);
		i++;
	}
	if (i == 1)
		return (ft_print_error(cmd[0], ERR_FWARGS, 0));
}

void ft_setenv(char **cmd, t_list **env, t_env_var *var)
{
	t_list **to_modify;
	char *newenv;

	if (cmd[3])
		return (ft_print_error(cmd[0], ERR_MNARGS, 0));
	if (!cmd[1])
		return (ft_display_env(*env));
	if (!ft_isalpha(cmd[1][0]))
		return (ft_print_error(cmd[0], ERR_FSTLTR, 0));
	if (!ft_str_match(cmd[1], ft_isalnum))
		return (ft_print_error(cmd[0], ERR_ALFA, 0));
	cmd[2] = cmd[2] ? cmd[2] : "";
	if ((newenv = ft_strnjoin(C_TAB{cmd[1], "=", cmd[2]}, 3)))
		if ((to_modify = ft_lstfind(env, cmd[1], ft_strlen(cmd[1]) + 1)))
		{
			ft_lstmodifone(*to_modify, newenv);
			ft_strreplace((*to_modify)->content, '=', 0);
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
	else
		new = ft_lstpushback(dup, cmd, len + 1);
}

void ft_env(t_list **env, char **cmd, t_env_var *var)
{
	t_list *dup;
	int i;

	if (!cmd[1] && env)
		return (ft_display_env(*env));
	dup = cmd[1] && ft_strequ(cmd[1], "-i") ? NULL : ft_lstdup(env);
	i = !dup;
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