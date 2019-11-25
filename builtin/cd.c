/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:20:37 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 23:21:02 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_get_cwd(char *ret, char *path)
{
	char *tmp;
	char *tmp2;
	int diff;

	while (*path)
	{
		if ((tmp = ft_strchr(path, '/')) || (tmp = ft_strchr(path, '\0')))
		{
			if ((diff = (tmp - path)) == 2 && ft_strnequ(path, "..", 2))
			{
				if (*ret && (tmp2 = ft_strrchr(ret, '/')))
					*tmp2 = 0;
			}
			else if (diff)
			{
				if ((tmp2 = ft_strrchr(ret, 0)) && (!*ret || tmp2[-1] != '/'))
					ft_strcat(tmp2, "/");
				ft_strncat(tmp2 + 1, path, diff);
			}
			path += diff + !!*tmp;
		}
	}
	!*ret ? ft_strcat(ret, "/") : 0;
}

void ft_update_pwd(char *pwd, t_env_var *var)
{
	ft_lstmodifone(var->oldpwd, ft_strjoin("OLDPWD=", var->pwd->content + 4));
	ft_lstmodifone(var->pwd, ft_strjoin("PWD=", pwd));
	ft_strreplace(var->oldpwd->content, '=', 0);
	ft_strreplace(var->pwd->content, '=', 0);
	free(pwd);
}

void ft_cd(char **cmd, t_env_var *var)
{
	char *path;

	if (cmd[1] && cmd[2])
		return (ft_print_error(cmd[0], ERR_MNARGS, 0));
	else if (!cmd[1])
		path = ft_strjoin(" ", var->home->content + 5);
	else if (ft_strequ(cmd[1], "-"))
		path = ft_strjoin(" ", var->oldpwd->content + 7);
	else if (!ft_is_dir(cmd[1]))
		return (ft_print_error(cmd[1], ERR_NOT_DIR, 0));
	else if (*cmd[1] != '/')
		path = ft_strnjoin(C_TAB{" ", var->pwd->content + 4, "/", cmd[1]}, 4);
	else
		path = ft_strjoin(" ", cmd[1]);
	if (path && !access(path + 1, F_OK))
	{
		*path = 0;
		ft_get_cwd(path, path + 2);
		if (!chdir(path))
			return (ft_update_pwd(path, var));
		free(path);
		return (ft_print_error(cmd[0], ERR_PRMDND, 0));
	}
	free(path);
	return (ft_print_error(cmd[0], ERR_NTFOUND, 0));
}