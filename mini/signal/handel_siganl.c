/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_siganl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:38 by youssef           #+#    #+#             */
/*   Updated: 2024/09/06 23:04:16 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal(int sig)
{
  (void)sig;
    free_garbage();
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void  handel_herdoc_segnal(int sig)
{
  if (sig == SIGINT)
  {
    close(STDIN_FILENO);
  }
}