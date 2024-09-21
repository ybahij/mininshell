/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:16:26 by youssef           #+#    #+#             */
/*   Updated: 2024/09/21 17:21:35 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_data;


t_garbage   **get_head(void)
{
  return (&g_data.garbage);
}

void exit_s(int status)
{
  g_data.status = status;
}

int ret_status(void)
{
  return (g_data.status);
}