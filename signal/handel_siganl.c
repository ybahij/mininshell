/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_siganl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:38 by youssef           #+#    #+#             */
/*   Updated: 2024/09/21 17:29:13 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal(int sig)
{
  if (sig == SIGINT)
  {
    exit_s(130);
    free_g();
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
  }
  return ;
}

// void  handle_signal2(int sig)
// {
//  if (sig == SIGINT)
//   {
//     printf("here\n");
//     free_garbage();
//     rl_on_new_line();
//     rl_replace_line("", 0);
//     rl_redisplay();
//   }
//   return ;
// }

void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
    write(1, "\n", 1);
		exit(2);
	}
}