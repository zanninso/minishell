/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:31:31 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/28 01:21:18 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_display_env(t_list *e)
{
	while (e)
	{
		if (e->content && e->content_size > 0)
			ft_printf("%s=%s", e->content, e->content + ft_strlen(e->content));
		e = e->next;
	}
}

void create_modify_env(t_list **env, char *key, char *val)
{
	t_list **ptr;

	if ((ptr = ft_lstfind(env, key, ft_strlen(key) + 1)))
	{
		val = ft_strnjoin(C_TAB{key, "=", val}, 3);
		ft_strreplace(val, '=', 0);
		ft_lstmodifone(*ptr, val);
	}
	else
	{
		val = ft_strnjoin(C_TAB{key, "=", val}, 3);
		ft_strreplace(val, '=', 0);
		ft_lstpushback(env, val, strlen(val));
		free(val);
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
		{
			if (ft_str_in_arr(cmd[i], C_TAB{PRINCIPALE_ENV_VAR, 0}))
				(*del)->content_size = 0;
			else
				ft_lstonedel(del);
		}
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
	create_modify_env(env, cmd[1], (cmd[2] ? cmd[2] : ""));
}

void ft_env(t_list **env, char **cmd, t_env_var *var)
{
	t_list *dup;
	char *val;
	int i;

	if (!cmd[1] && env)
		return (ft_display_env(*env));
	dup = cmd[1] && ft_strequ(cmd[1], "-i") ? NULL : ft_lstdup(env);
	i = !dup;
	while (cmd[++i])
	{
		if ((val = ft_strchr(cmd[i], '=')) && ft_strreplace(cmd[i], '=', 0))
			create_modify_env(&dup, cmd[i], val + 1);
		else
		{
			ft_shellmain(cmd + i, dup, var);
			break;
		}
	}
	if (!cmd[i])
		(ft_display_env(dup));
}