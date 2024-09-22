/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:22:20 by youssef           #+#    #+#             */
/*   Updated: 2024/09/22 21:02:03 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global g_data;

void  *ft_malloc(size_t size)
{
    t_garbage *tmp;
    void *tmp2;
    tmp2 = malloc(size);
    if (!tmp2)
    {
        g_data.fall = 1;
        printf(MAGENTA"Error: malloc failed\n"RESET);
        return (NULL);
    }
    tmp = malloc(sizeof(t_garbage));
    if (!tmp)
    {
        free(tmp2);
        g_data.fall = 1;
        printf(MAGENTA"Error: malloc failed\n"RESET);
        return (NULL);
    }
    tmp->content = tmp2;
    tmp->next = *get_head();
    *get_head() = tmp;
    return (tmp2);
}

void    add_garbage(void *content)
{
    t_garbage *tmp;

    tmp = malloc(sizeof(t_garbage));
    if (!tmp)
    {
        g_data.fall = 1;
        printf(MAGENTA"Error: malloc failed\n"RESET);
        return ;
    }
    tmp->content = content;
    tmp->next = *get_head();
    *get_head() = tmp;
}

void    free_g(void)
{
    t_garbage *tmp;

    if (!*get_head())
        return ;
    while (*get_head())
    {
        tmp = (*get_head())->next;
        if ((*get_head())->content)
          free((*get_head())->content);
        free(*get_head());
        *get_head() = tmp;
    }
    *get_head() = NULL;
}