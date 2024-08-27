#include "minishell.h"

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

char **get_cmd_args(lexer_t *token)
{
  char **str;
  int len;
  lexer_t *tmp;
  int i;

  len = 0;
  tmp = token;
  while (tmp)
  {
    if (tmp->type == 'w' || tmp->type == 'q')
      len++;
    tmp = tmp->next;
  }
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

t_cmd *parse_redir(lexer_t *head)
{
    lexer_t *token;
    t_redir *redir;
    t_heredoc *heredoc;

    token = head;
    while (token)
    {
        if (cm_strchr("<>+h", token->type))
            break ;
        token = token->next;
    }
    if (token && cm_strchr("<>+", token->type))
    {
        redir = malloc(sizeof(t_redir));
        redir->type = REDIRECTION;
        redir->file = ft_strdup(token->next->content);
        handle_redirection(redir, token);
        token->type = 'p';
        token->next->type = 'p';
        redir->next = parse_redir(head);
        return ((t_cmd *)redir);
    }
    else if (token && token->type == 'h')
    {
        heredoc = malloc(sizeof(t_redir));
        heredoc->type = HEREDOC;
        heredoc->content = ft_strdup(token->next->content);
        token->type = 'p';
        token->next->type = 'p';
        heredoc->next = parse_redir(head);
        return ((t_cmd *)heredoc);
    }
    else
        return (parse_cmd(head));
}

t_cmd *parse_pipe(lexer_t *head)
{
    lexer_t *token;
    t_pipe  *pipe;

    token = peek(head, '|');
    if (token)
    {
        pipe = malloc(sizeof(t_pipe));
        if (!pipe)
            return (NULL);
        pipe->type = PIPE;
        token->prev->next = NULL;
        token->next->prev = NULL;
        pipe->left = parse_redir(head);
        pipe->right = parse_pipe(token->next);
        free(token->content);
        free(token);
        return((t_cmd *)pipe);
    }
    else
        return(parse_redir(head));
}

t_cmd *parse_or(lexer_t *head)
{
    lexer_t *token;
    t_or    *or;

    token = peek(head, 'o');
    if (token)
    {
        or = malloc(sizeof(t_or));
        if (!or)
            return (NULL);
        or->type = OR;
        token->prev->next = NULL;
        token->next->prev = NULL;
        or->left = parse_pipe(head);
        or->right = parse_or(token->next);
        free(token->content);
        free(token);
        return((t_cmd *)or);
    }
    else
        return(parse_pipe(head));
}

t_cmd *parse_and(lexer_t *head)
{
    lexer_t *token;
    t_and   *and;

    token = peek(head, '&');
    if (token)
    {
        and = malloc(sizeof(t_and));
        if (!and)
            return (NULL);
        and->type = AND;
        token->prev->next = NULL;
        token->next->prev = NULL;
        and->left = parse_or(head);
        and->right = parse_and(token->next);
        free(token->content);
        free(token);
        return((t_cmd *)and);
    }
    else
        return(parse_or(head));
}