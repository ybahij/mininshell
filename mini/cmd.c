// #include"libft.h"

// lexer_t *peek(lexer_t *head, char type)
// {
//     while (head)
//     {
//         if (head->type == type)
//             return (head);
//         head = head->next;
//     }
//     return (NULL);
// }

// int handle_redirection(t_redir *redir, lexer_t *token)
// {
//     if (token->type == '>')
//     {
//         redir->mode = 
//     }
// }

// t_cmd *parse_redir(lexer_t *head)
// {
//     lexer_t *token;
//     t_redir *redir;

//     token = head;
//     while (token)
//     {
//         if (cm_strchr("<>+h", token->type))
//             break ;
//         token = token->next;
//     }
//     if (token)
//     {
//         redir = malloc(sizeof(t_redir));
//         redir->type = REDIRECTION;
//         redir->file = token->next->content;
//         handle_redirection(redir, token);
//     }
// }

// t_cmd *parse_pipe(lexer_t *head)
// {
//     lexer_t *token;
//     t_pipe  *pipe;

//     token = peek(head, '|');
//     if (token)
//     {
//         pipe = malloc(sizeof(t_pipe));
//         if (!pipe)
//             return (NULL);
//         pipe->type = PIPE;
//         token->prev->next = NULL;
//         token->next->prev = NULL;
//         pipe->left = parse_redir(head);
//         pipe->right = parse_pipe(token->next);
//         return((t_cmd *)pipe);
//     }
//     else 
//         return(parse_redir(head));
// }