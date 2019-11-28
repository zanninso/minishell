/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/28 01:17:10 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void ft_display_prompt(char *prt)
{
	char *path;

	path = ft_strrchr(prt + 1,'/');
	path = path ? path + 1 : prt;
	ft_printf("%s➜\e[0m  \e[1m\e[96m%s\e[0m ", "\e[92m", path);
	// ft_printf("%s➜\e[0m  \e[1m\e[96m%s\e[0m ", "\e[91m", path);
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
	t_list **ptr;

	pwd = &var->pwd;
	*env = tab_to_list(environ);
	signal(SIGINT, kill_procces);
	if((ptr = ft_lstfind(env, "HOME", 5)))
		var->home = *ptr;
	else if(var->home = ft_lstnew("HOME=", 5))
		ft_lstadd(env,var->home);
	if((ptr = ft_lstfind(env, "PWD", 4)))
		var->pwd = *ptr;
	else if(var->pwd = ft_lstnew("PWD=", 4))
		ft_lstadd(env,var->pwd);
	if((ptr = ft_lstfind(env, "PATH", 5)))
		var->path = *ptr;
	else if(var->path = ft_lstnew("PATH=", 5))
		ft_lstadd(env,var->path);
	if((ptr = ft_lstfind(env, "OLDPWD", 7)))
		var->oldpwd = *ptr;
	else if(var->oldpwd = ft_lstnew("OLDPWD=", 5))
		ft_lstadd(env,var->oldpwd);
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
		ft_env(env, cmd, var);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_setenv(cmd, env, var);
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd, env);
	else
		ft_shellmain(cmd, *env, var);

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