/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:47:48 by youssef           #+#    #+#             */
/*   Updated: 2024/08/28 17:25:29 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_cmd_len(lexer_t *token)
{
    int len;
    lexer_t *tmp;

    len = 0;
    tmp = token;
    while (tmp)
    {
        if (tmp->type == 'w' || tmp->type == 'q')
            len++;
        tmp = tmp->next;
    }
    return (len);
}

char **get_cmd_args(lexer_t *token)
{
  char **str;
  int len;
  lexer_t *tmp;
  int i;

  len = 0;
  len = get_cmd_len(token);
  str = malloc(sizeof(char *) * (len + 1));
  if (!str)
    return (NULL);
  tmp = token;
  i = 0;
  while (tmp)
  {
    if (tmp->type == 'w' || tmp->type == 'q')
    {
      str[i] = ft_strdup(tmp->content);
      i++;
    }
    tmp = tmp->next;
  }
  str[i] = NULL;
  return (str);
}

t_cmd *parse_cmd(lexer_t *token)
{
    t_exec  *cmd;

    cmd = malloc(sizeof(t_exec));
    cmd->type = EXEC;
    cmd->av = get_cmd_args(token);
    free_list(token);
    return ((t_cmd *)cmd);
}




