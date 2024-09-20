/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:22:20 by youssef           #+#    #+#             */
/*   Updated: 2024/09/19 15:21:47 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// t_garbage   **get_head(void)
// {
//     static t_garbage *head;

//     return (&head);
// }

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
        free_g(*get_head());
        exit(1);
    }
    tmp = malloc(sizeof(t_garbage));
    if (!tmp)
    {
        free(tmp2);
        free_g(*get_head());
        printf(MAGENTA"Error: malloc failed\n"RESET);
        exit(1);
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
        free_g(*get_head());
        printf(MAGENTA"Error: malloc failed\n"RESET);
        exit(1);
    }
    tmp->content = content;
    tmp->next = *get_head();
    *get_head() = tmp;
}

void    free_garbage(void)
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
}