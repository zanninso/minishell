/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 22:47:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_access(char *cmd)
{
	if (cmd && !access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (0);
		else
			return (2);
	}
	return (1);
}

char *find(char *cmd, t_env_var *var)
{
	char *path;
	int ret;
	int permdeny;
	char **paths;
	int i;

	permdeny = 0;
	i = 0;
	paths = ft_strsplit(var->path->content + 5, ":");
	while (paths && paths[i])
	{
		path = ft_strnjoin(C_TAB{paths[i], "/", cmd}, 3);
		if (!(ret = cmd_access(path)))
		{
			ft_free_2d_tab(paths);
			return (path);
		}
		i++;
		ret == 2 ? permdeny = ret : 0;
		free(path);
	}
	ft_free_2d_tab(paths);
	ft_print_error(cmd, permdeny, 0);
	return (NULL);
}

int execut_cmd(char *cmd, char **cmd_arg, t_list *env)
{
	pid_t parrent;
	int ret;
	char **tab_env;

	ret = -1;
	tab_env = list_to_tab(env, 1);
	parrent = 0;
	parrent = fork();
	child_prc_pid = parrent;
	if (parrent < 0)
	{
		ft_free_2d_tab(tab_env);
		return (1);
	}
	if (parrent > 0)
	{
		wait(&ret);
		if (WIFSIGNALED(ret))
			ft_putstr("\n");
	}
	if (parrent == 0)
		execve(cmd, cmd_arg, tab_env);
	ft_free_2d_tab(tab_env);
	return (ret);
}

int ft_shellmain(char **cmd, t_list *env, t_env_var *var)
{
	char *cmd_path;
	int ret;

	if (ft_strchr(cmd[0], '/'))
	{
		if ((ret = cmd_access(cmd[0])))
		{
			ft_print_error(cmd[0], ret, 0);
			return (-1);
		}
		cmd_path = ft_strdup(cmd[0]);
	}
	else
		cmd_path = find(cmd[0], var);
	if (cmd_path)
	{
		ret = execut_cmd(cmd_path, cmd, env);
		free(cmd_path);
		return (ret);
	}
	else
		return (-1);
}