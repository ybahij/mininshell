/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:44:31 by youssef           #+#    #+#             */
/*   Updated: 2024/08/31 18:32:24 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

lexer_t *peek(lexer_t *head, char type)
{
    while (head)
    {
        if (head->type == type)
            return (head);
        head = head->next;
    }
    return (NULL);
}

t_cmd *parse_or(lexer_t *head, char **env)
{
    lexer_t *token;
    t_or    *or;

    token = peek(head, 'o');
    if (token)
    {
        or = ft_malloc(sizeof(t_or));
        if (!or)
            return (NULL);
        or->type = OR;
        token->prev->next = NULL;
        token->next->prev = NULL;
        or->left = parse_pipe(head, env);
        or->right = parse_or(token->next, env);
        return((t_cmd *)or);
    }
    else
        return(parse_pipe(head, env));
}

t_cmd *parse_and(lexer_t *head, char **env)
{
    lexer_t *token;
    t_and   *and;

    token = peek(head, '&');
    if (token)
    {
        and = ft_malloc(sizeof(t_and));
        if (!and)
            return (NULL);
        and->type = AND;
        token->prev->next = NULL;
        token->next->prev = NULL;
        and->left = parse_or(head, env);
        and->right = parse_and(token->next, env);
        return((t_cmd *)and);
    }
    else
        return(parse_or(head, env));
}