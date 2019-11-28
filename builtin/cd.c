/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:20:37 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/28 00:50:22 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_get_cwd(char *ret, char *path)
{
	char *tmp;
	char *tmp2;
	int diff;

	*ret = 0;
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

void ft_update_pwd(char *path, t_env_var *var)
{
	const char *pwd = var->pwd->content;
	const char *oldpwd = var->oldpwd->content;

	var->oldpwd->content = ft_strjoin("OLDPWD=", (pwd ? pwd + 4 : ""));
	var->pwd->content = ft_strjoin("PWD=", (path ? path : ""));
	ft_strreplace(var->oldpwd->content, '=', 0);
	ft_strreplace(var->pwd->content, '=', 0);
	if(pwd)
		var->pwd->content_size = 4 + strlen(path);
	if(oldpwd)
		var->pwd->content_size = 7 + (pwd ? strlen(pwd + 4) : 0);
	free(pwd);
	free(oldpwd);
	free(path);
}

int change_dir(t_env_var *var, char *path)
{
	char *dir;

	if (path && !access(path + 1, F_OK))
	{
		ft_get_cwd(path, path + 2);
		if (!chdir(path))
		{
			ft_update_pwd(path, var);
			return(0);
		}
		free(path);
		return (ft_printf("%s : %s : %s", dir, ERR_NTFOUND, 0));
	}
	return (ft_printf("%s : %s : %s", dir, ERR_NTFOUND, 0));
}

void ft_cd(char **cmd, t_list **env, t_env_var *var, char *path)
{
	t_list **elm;

	if (cmd[1] && cmd[2])
		return (ft_printf("%s : %s : %s", cmd[0], ERR_NTFOUND, 0));
	else if (!cmd[1])
	{
		if (!var->home->content)
			return (ft_printf("%s : %s : %s", cmd[0], ERR_NTFOUND, 0));
		path = ft_strjoin(" ", var->home->content + 5);
	}
	else if (ft_strequ(cmd[1], "-"))
	{
		if (!var->oldpwd->content)
			return (ft_printf("%s : %s : %s", cmd[0], ERR_NTFOUND, 0));
		path = ft_strjoin(" ", var->oldpwd->content + 7);
	}
	else if (*cmd[1] != '/')
	{
		if (var->pwd->content)
			path = ft_strnjoin(C_TAB{" ", &var->pwd->content[4], "/", cmd[1]}, 4);
		else
			path = ft_strnjoin(C_TAB{" ", getcwd(NULL, 0), "/", cmd[1]}, 4);
	}
	return (change_dir(var, path));
}
