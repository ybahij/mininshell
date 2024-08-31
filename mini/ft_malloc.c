/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:22:20 by youssef           #+#    #+#             */
/*   Updated: 2024/08/31 21:37:34 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_garbage *g_head;

void  free_g(t_garbage *head)
{
    t_garbage *tmp;

    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

void  *ft_malloc(size_t size)
{
    t_garbage *tmp;
    void *tmp2;
    tmp2 = malloc(size);
    if (!tmp2)
    {
        free_g(g_head);
        exit(1);
    }
    tmp = malloc(sizeof(t_garbage));
    if (!tmp)
    {
        free(tmp2);
        free_g(g_head);
        printf(MAGENTA"Error: malloc failed\n"RESET);
        exit(1);
    }
    tmp->content = tmp2;
    tmp->next = g_head;
    g_head = tmp;
    return (tmp2);
}

void    add_garbage(void *content)
{
    t_garbage *tmp;

    tmp = malloc(sizeof(t_garbage));
    if (!tmp)
    {
        free_g(g_head);
        printf(MAGENTA"Error: malloc failed\n"RESET);
        exit(1);
    }
    tmp->content = content;
    tmp->next = g_head;
    g_head = tmp;
}

void    free_garbage(void)
{
    t_garbage *tmp;

    if (!g_head)
        return ;
    while (g_head)
    {
        tmp = g_head->next;
        if (g_head->content)
          free(g_head->content);
        free(g_head);
        g_head = tmp;
    }
}