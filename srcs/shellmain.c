/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 00:44:53 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int cmd_access(char *cmd)
{
    if (!is_dir(cmd) && !access(cmd, F_OK))
    {
        if (!access(cmd, X_OK))
            return (1);
        else
            return (2);
    }
    return (0);
}

char *find(char *cmd, t_list **env)
{
    char *path;
    int i;
    int ret;
    int permdeny;
    char **paths;
    t_list **getpath;

    i = 0;
    paths = NULL;
    permdeny = 0;
    if ((getpath = ft_lstfind(env, "PATH", 5)))
    {
        paths = ft_strsplit((*getpath)->content + 5, ':');
        while (paths[i])
        {
            path = ft_strnjoin((char *[]){paths[i], "/", cmd}, 3);
            if ((ret = cmd_access(path)) == 1)
            {
                freetab(paths);
                return (path);
            }
            ret == 2 ? permdeny = ret : 0;
            free(path);
            i++;
        }
    }
    freetab(paths);
    ft_print_error(cmd, permdeny, 0);
    return (NULL);
}

int ft_shellmain(char **cmd, t_list *env)
{
    pid_t parrent = 0;
    char *cmd_path;
    char **tab_env;
    int ret;

    cmd_path = NULL;
    if ((ret = cmd_access(cmd[0])))
    {
         ret == 1 ? cmd_path = cmd[0] : 0;
         ret == 2 ? ft_print_error(cmd[0], ret, 0) : 0;
         if (ret == 2)
            return (0);
    }
    else if (!cmd_path)
        cmd_path = find(cmd[0], &env);
    if (cmd_path)
    {
        tab_env = list_to_tab(env, 1);
        parrent = fork();
        child_prc_pid = parrent;
        if (parrent < 0)
            return (0); // Fork error exit(Failure)
        if (parrent > 0)
        {
            wait(&ret);
            if(WIFSIGNALED(ret))
                ft_putstr("\n");
        }
        if (parrent == 0)
            execve(cmd_path, cmd, tab_env);
        // free tab
        return (1);
    }
    else
        return (0);
}