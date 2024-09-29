/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:10:14 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/29 10:21:21 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_pid(void)
{
    t_pid	*tmp;
    t_pid	*tmp2;

    tmp = g_data.pid;
    while (tmp)
    {
        tmp2 = tmp->next;
        kill(tmp->pid, SIGKILL);
        tmp = tmp2;
    }
    g_data.pid = NULL;
}

void heandl_signal_child(int status)
{
    if (status == SIGINT)
    {
        free_g();
        exit_s(130);
        exit(130);
    }
    if (status == SIGQUIT)
    {
        free_g();
        exit_s(131);
        exit (131);
    }
}