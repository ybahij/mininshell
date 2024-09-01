/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:46:23 by youssef           #+#    #+#             */
/*   Updated: 2024/09/01 16:49:54 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_redirection(t_redir *redir, lexer_t *token)
{
    if (token->type == '<')
    {
        redir->mode = O_RDONLY;
        redir->fd = 0;
    }
    else if (token->type == '>')
    {
        redir->mode = O_CREAT | O_WRONLY | O_TRUNC;
        redir->fd = 1;
    }
    else if (token->type == '+')
    {
        redir->mode = O_CREAT | O_WRONLY | O_APPEND;
        redir->fd = 1;
    }
}

t_cmd   *herdoc_construct(lexer_t *token, lexer_t *head,char **env)
{
    t_heredoc *heredoc;

    heredoc = ft_malloc(sizeof(t_redir));
    heredoc->type = HEREDOC;
    heredoc->content = ft_strdup(token->next->content);
    token->type = 'p';
    token->next->type = 'p';
    heredoc->next = parse_redir(head, env);
    return ((t_cmd *)heredoc);
}

t_cmd *redir_construct(lexer_t *token, lexer_t *head, char **env)
{
    t_redir *redir;

    redir = ft_malloc(sizeof(t_redir));
    redir->type = REDIRECTION;
    redir->file = ft_strdup(token->next->content);
    handle_redirection(redir, token);
    token->type = 'p';
    token->next->type = 'p';
    redir->next = parse_redir(head, env);
    return ((t_cmd *)redir);
}

t_cmd *parse_redir(lexer_t *head, char **env)
{
    lexer_t *token;
    t_redir *redir;

    token = head;
    while (token)
    {
        if (cm_strchr("<>+h", token->type))
            break ;
        token = token->next;
    }
    if (token && cm_strchr("<>+", token->type))
        return (redir_construct(token, head, env));
    else if (token && token->type == 'h')
        return (herdoc_construct(token, head, env));
    else
        return (parenthesis_c(head, env));
}

t_cmd *parse_pipe(lexer_t *head, char **env)
{
    lexer_t *token;
    t_pipe  *pipe;

    token = peek(head, '|');
    if (token)
    {
        pipe = ft_malloc(sizeof(t_pipe));
        if (!pipe)
            return (NULL);
        pipe->type = PIPE;
        token->prev->next = NULL;
        token->next->prev = NULL;
        pipe->left = parse_redir(head, env);
        pipe->right = parse_pipe(token->next, env);
        return((t_cmd *)pipe);
    }
    else
        return(parse_redir(head, env));
}