/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:20:37 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/27 18:38:32 by aait-ihi         ###   ########.fr       */
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

void ft_update_pwd(char *path, t_list **env)
{
	t_list **pwd;
	t_list **oldpwd;

	pwd = ft_lstfind(env, "PWD", 4);
	oldpwd = ft_lstfind(env, "OLDPWD", 7);

	ft_lstmodifone(var->oldpwd, ft_strjoin("OLDPWD=", var->pwd->content + 4));
	ft_lstmodifone(var->pwd, ft_strjoin("PWD=", pwd));
	ft_strreplace(var->oldpwd->content, '=', 0);
	ft_strreplace(var->pwd->content, '=', 0);
	free(pwd);
}

int change_dir(char *path, t_list **env, char *oldwd)
{
	char *dir;

	if (path && !access(path + 1, F_OK))
	{
		*path = 0;
		ft_get_cwd(path, path + 2);
		if (!chdir(path))
		{
			oldwd = path;
			ft_update_pwd(path, env);
		}
		free(path);
		return (ft_printf("%s : %s : %s",dir, ERR_NTFOUND, 0));
	}
	return (ft_printf("%s : %s : %s",dir, ERR_NTFOUND, 0));
}

void ft_cd(char **cmd, t_list **env, char *oldpwd, char *path)
{
	t_list **elm;

	if (cmd[1] && cmd[2])
		return (ft_printf("%s : %s : %s",cmd[0], ERR_NTFOUND, 0));
	else if (!cmd[1])
	{
		if(!(elm = ft_lstfind(env, "HOME", 5)))
			return (ft_printf("%s : %s : %s",cmd[0], ERR_NTFOUND, 0));
		path = ft_strjoin(" ", (*elm)->content + 5);	
	}
	else if (ft_strequ(cmd[1], "-"))
	{
		if(!oldpwd)
			return (ft_printf("%s : %s : %s",cmd[0], ERR_NTFOUND, 0));
		path = ft_strjoin(" ", oldpwd);		
	}
	else if (*cmd[1] != '/')
	{
		if(!(elm = ft_lstfind(env, "PWD", 4)))
			path = ft_strnjoin(C_TAB{" ", &(*elm)->content[4], "/", cmd[1]}, 4);
		else
			path = ft_strnjoin(C_TAB{" ", getcwd(NULL, 0), "/", cmd[1]}, 4);
	}
	return (change_dir(path));
}
