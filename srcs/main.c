/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 03:50:47 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void ft_display_prompt(char *prt)
{
	ft_putstr("-> ");
	ft_putstr(ft_strrchr(prt,'/'));
	ft_putstr(" $>");
}

void kill_procces(int signal)
{
	(void)signal;
	if (child_prc_pid == 0)
	{
		ft_putstr("\n");
		ft_display_prompt((*pwd)->content + 4);
	}
}

void init(char *environ[], t_list **env, t_env_var *var)
{
	*env = tab_to_list(environ);
	signal(SIGINT, kill_procces);
	var->home = *ft_lstfind(env, "HOME", 5);
	var->pwd = *ft_lstfind(env, "PWD", 4);
	var->oldpwd = *ft_lstfind(env, "OLDPWD", 7);
	var->path = *ft_lstfind(env, "PATH", 5);
	pwd = &var->pwd;
}

void dispatch(char **cmd, t_list **env, t_env_var *var)
{
	if (!cmd[0])
		return ;
	else if (ft_strequ(cmd[0], "exit"))
		{ 
			freetab(cmd);
			ft_lstdel(env, &freecontent);
			exit(0);
		}
	else if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd, var);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd[0], "env"))
		ft_env(env, cmd);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_setenv(cmd, env, var);
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd, env);
	else
		ft_shellmain(cmd, *env);

}

int main(int ac, char *av[], char *environ[])
{
	char *buffer;
	char **cmd;
	t_list *env;
	t_list *lstcmd;
	t_env_var var;

	(void)ac;
	(void)**av;
	init(environ, &env, &var);
	while (1)
	{
		ft_display_prompt(var.pwd->content + 4);
		if (get_next_line(0, &buffer) > 0)
		{
			lstcmd = ft_parsecmd(buffer, &env, &var);
			//printlist(lstcmd);
			cmd = list_to_tab(lstcmd, 0);
			// printmatrix(cmd);
			ft_lstdel(&lstcmd, &freecontent);
			dispatch(cmd, &env, &var);
			//free CMD
		}
		child_prc_pid = 0;
	}
	return (0);
}