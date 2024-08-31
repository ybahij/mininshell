/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:03:24 by youssef           #+#    #+#             */
/*   Updated: 2024/08/31 18:56:48 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char  *remaove_parenthesis(char *content)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    str = ft_substr(content, 1, ft_strlen(content) - 2);
    return (str);
}

t_cmd   *parenthesis_c(lexer_t *head, char **env)
{
    lexer_t *token;
    lexer_t *tok;

    token = peek(head, '(');
    if (token)
    {
      head->content = remaove_parenthesis(head->content);
      token_cmd(head->content, &tok, env);
      return (parse_and(tok, env));
    }
    else
      return (parse_cmd(head));
}

