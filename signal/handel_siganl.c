/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_siganl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:38 by youssef           #+#    #+#             */
/*   Updated: 2024/09/24 17:48:17 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal(int sig)
{
  if (sig == SIGINT)
  {
    exit_s(130);
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
  }
  return ;
}

void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
    close(set_fd(0, 1));
    free_g();
    write(1, "\n", 1);
		exit(2);
	}
}