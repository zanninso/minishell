#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include "../libft/includes/libft.h"
#define C_TAB (char *[])
#define PID "12452"
#define PRINCIPALE_ENV_VAR "HOME", "PWD", "OLDPWD", "PATH"

pid_t child_prc_pid;
t_list **pwd;

enum
{
	ERR_CMDNTFD,
	ERR_MNARGS,
	ERR_PRMDND,
	ERR_FWARGS,
	ERR_FSTLTR,
	ERR_ALFA,
	ERR_NOT_DIR,
	ERR_NTFOUND,
	ERR_UKNUSR,
	ERR_UNMATCHED,
};

typedef struct s_env_var
{
	t_list *home;
	t_list *pwd;
	t_list *oldpwd;
	t_list *path;
} t_env_var;

//parse
t_list *ft_parsecmd(char *buffer, t_list **env, t_env_var *var);

//debug
void printmatrix(char **tab);
void printlist(t_list *env);

//
int ft_shellmain(char **cmd, t_list *env, t_env_var *var);
t_list *tab_to_list(char **env);
char **list_to_tab(t_list *env, int flag);

// bultins
void ft_echo(char **cmd);
void ft_env(t_list **env, char **cmd, t_env_var *var);
void ft_cd(char **cmd, t_env_var *env_var);
t_list *isenv(char *str, t_env_var *var);
void ft_setenv(char **cmd, t_list **env, t_env_var *var);
void ft_unsetenv(char **cmd, t_list **env);

//utils
t_list **ft_lstfind(t_list **lst, const char *needle, size_t size);
void ft_lstonedel(t_list **to_del);
void ft_lstdelvar(t_list **to_del);
void ft_lstmodifone(t_list *to_mod, char *value);
t_list *ft_lstdup(t_list **env);
void ft_display_prompt(char *prt);

//errors
void ft_print_error(char *str, int er, char c);

//free
void	freecontent(void *content, size_t contentsize);
void    freetab (char **tab);

// env 

void ft_display_env(t_list *env);
#endif