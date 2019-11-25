/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:31:31 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 23:32:21 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unsetenv(char **cmd, t_list **env)
{
    int i;
    t_list **del;

    i = 1;
    while (cmd[i])
    {
		del = ft_lstfind(env, cmd[i], ft_strlen(cmd[i]) + 1);
		if (del && ft_str_in_arr(cmd[i], C_TAB{PRINCIPALE_ENV_VAR, 0}))
			*del = (*del)->next;
		else if(del)
			ft_lstonedel(del);
    }
    if (i == 1)
    	return (ft_print_error(cmd[0], ERR_FWARGS, 0));
}
