#include "libft.h"

int pars_quote(char *content)
{
   int i = 0;
    int quote = 0;

   while (content[i])
    {
         if (content[i] == '\'' || content[i] == '\"')
        {
            quote = content[i];
            i++;
            while (content[i] && content[i] != quote)
                i++;
            if (content[i] != quote)
            {
                printf(RED"minishell: syntax error near unexpected token `%c'\n"RESET, quote);
                return (0);
            }
        }
        if (content[i])
           i++;
    }
    return (1);
}

int pars_(lexer_t *tmp)
{
    lexer_t *tmp2;

    tmp2 = tmp->next;
    if (!tmp2 )
    {
        printf(RED"minishell: syntax error near unexpected token `%s'\n"RESET, tmp->content);
        return (0);
    }
    if (cm_strchr("><+h", tmp2->type) && tmp->type != '|')
    {
        printf("Syntax error near unexpected token '%s'\n", tmp2->content);
        return (0);
    }
    if (cm_strchr("|&o", tmp->type) && cm_strchr("|&o", tmp2->type))
    {
        printf("Syntax error near unexpected token '%s'\n", tmp2->content);
        return (0);
    }
    return (1);
}

int cmd_syntax(lexer_t *tmp)
{
    if (!tmp)
        return (0);
    if (cm_strchr("|o&", tmp->type))
        return (printf(RED"minishell: syntax error near unexpected token `%s'\n"RESET, tmp->content), 1);
    while (tmp)
    {
        if (cm_strchr("|<>oh+&", tmp->type))
        {
            if (!pars_(tmp))
                return (1);
        }
        if (tmp->type == 'q')
        {
            if (!pars_quote(tmp->content))
                return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

void    free_(lexer_t *cmd)
{
    lexer_t *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        free(cmd->content);
        free(cmd);
        cmd = tmp;
    }
}

char *cheak_env(char *str, char **env)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *tmp;

    tmp = NULL;
    while (env[i])
    {
        j = 0;
        if (ft_strncmp(env[i], str, ft_strlen(str)))
        {
            i++;
            continue;
        }
        if (env[i][ft_strlen(str)] == '=')
            tmp = ft_strdup(&env[i][ft_strlen(str) + 1]);
        if (tmp)
            break;
        i++;
    }
    free(str);
    return (tmp);
}

int appand_u(int *j, int i, lexer_t *cmd, int fd, char **env)
{
    char *tmp2;
    int len;
    int k;

    len = 0;
    k = i;
    while (cmd->content[k] && (ft_isalnum(cmd->content[k]) && !cm_strchr("\"'$", cmd->content[k])))
        k++;
    tmp2 = cheak_env(ft_substr(cmd->content, i, k - i), env);
    if (tmp2)
        len += write(fd, tmp2, ft_strlen(tmp2));
    free(tmp2);
    *j = k;
    return (len);
}



int appand_in_fille(lexer_t *cmd, int fd, char **env)
{
    int len;
    int i;
    char hold;
    int j;

    i = 0;
    j = 0;
    len = 0;
    hold = 0;
    while (cmd->content[i])
    {
        if ((cmd->content[i] == '"' || cmd->content[i] == '\'') && hold == 0)
            hold = cmd->content[i];
        else if (cmd->content[i] == hold)
            hold = 0;
        if (hold != '\'' && cmd->content[i] == '$' && !cm_strchr("!@#\%^&*$()=+\\|[]{};\"\':/?.", cmd->content[i + 1]))
        {
            i++;
            len += appand_u(&j, i, cmd, fd, env);
            i = j;
        }
        else
            len += write(fd, &cmd->content[i++], 1);
    }
    return (len);
}

void    free_array(char **str)
{
    int i = 0;

    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}


int expand_w(lexer_t *cmd, char **env)
{
    char *tmp2;
    int fd[2];
    char fname[10];
    int rfd;
    int len;

    if (cmd->prev)
    {
        if (cmd->prev->type == 'h')
            return (1);
    }
    len = 0;
    pipe(fd);
    cmd->b_appand = ft_strdup(cmd->content);
    len = appand_in_fille(cmd, fd[1], env);
    close(fd[1]);
    rfd = fd[0];
    free(cmd->content);
    cmd->content = malloc(len + 2);
    read(fd[0], cmd->content, len);
    cmd->content[len] = '\0';
    close(fd[0]);
    return (0);
}

int     free_list(lexer_t *head)
{
    lexer_t *tmp;

    while (head)
    {
        tmp = head->next;
        free(head->content);
        if (head->b_appand)
            free(head->b_appand);
        free(head);
        head = tmp;
    }
    return (0);
}

int    expand(lexer_t *cmd, char **env)
{
    lexer_t *tmp;
    lexer_t *tmp2;

    tmp = cmd;
    while (tmp)
    {
        if (cm_strchr(tmp->content, '$'))
        {
            if (tmp->prev && tmp->prev->type == 'h')
            {
                tmp = tmp->next;
                continue;
            }
            expand_w(tmp, env);

            if (!tmp->content[0] && tmp->prev && cm_strchr("<>+", tmp->prev->type))
            {
                printf(RED"minishell: %s: ambiguous redirect\n"RESET, tmp->b_appand);
                return (free_list(cmd), 1);
            }
        }
        tmp = tmp->next;
    }
    return (0);
}

char *dellt_q(lexer_t *cmd, int i)
{
    char *tmp;
    char    hold;

    tmp = cmd->content;
    cmd->content = NULL;
    while (tmp[i])
    {
        if (tmp[i] == '"' || tmp[i] == '\'')
        {
            hold = tmp[i];
            i++;
            while(tmp[i] && tmp[i] != hold)
            {
                cmd->content = ft_strjoin(cmd->content, ft_substr(tmp, i, 1));
                i++;
            }
        }
        else
            cmd->content = ft_strjoin(cmd->content, ft_substr(tmp, i, 1));
        if (tmp[i])
            i++;
    }
    free(tmp);
    return (cmd->content);
}

int del_quote(lexer_t *cmd)
{
    int i;
    int j;
    char *tmp;
    char hold;

    while (cmd)
    {
        if (!cm_strchr("|<>oh+&", cmd->type))
            cmd->content = dellt_q(cmd, 0);
        cmd = cmd->next;
    }
    return (0);
}

lexer_t *split_1(lexer_t *head, char **str, int i)
{
    lexer_t *tmp;
    lexer_t *tmpl;

    tmp = head->next;
    free(head->content);
    head->content = str[0];
    head->next = NULL;
    i = 1;
    while (str[i])
    {
        tmpl = lexer(str[i], 'w');
        ft_lstadd_back(&head, tmpl);
        i++;
    }
    free(str);
    tmpl = ft_lstlast(head);
    tmpl->next = tmp;
    if (tmp)
        tmp->prev = tmpl;

    return (tmp);
}

lexer_t *spilt_(lexer_t *head)
{
    lexer_t *n_head = NULL;
    char **str;
    char *tmp;
    int i = 0;

    if (!head || !(str = ft_split(head->content)))
        return NULL;
    while (str[i])
        i++;
    if (i > 1)
    {
        if (head->prev && cm_strchr("+><", head->prev->type))
        {
            printf(RED"minishell: %s: ambiguous redirect\n"RESET, head->content);
            free(head->b_appand);
            head->b_appand = NULL;
            head->b_appand = ft_strdup("ambiguous redirect");
            return (free_array(str), head);
        }
        return (split_1(head, str, i));
    }
    tmp = head->content;
    head->content = ft_strdup(str[0]);
    free(tmp);
    free_array(str);
    return (head->next);
}



int split_cmd(lexer_t *head) {
    lexer_t *tmp = head;

    while (tmp) {
        if (cm_strchr(tmp->content, ' '))
        {
            tmp = spilt_(tmp);
            if (tmp && !ft_strncmp(tmp->b_appand, "ambiguous redirect", 18))
            {
                free(tmp->b_appand);
                tmp->b_appand = NULL;
                return (free_list(head), 0);
            }
        }
        else
            tmp = tmp->next;
    }

    return (1);
}


int main(int ac, char **av, char **env)
{
    char *line = NULL;
    lexer_t *cmd;
    lexer_t *tmp;
    lexer_t *tmp2;
    int i = 0;

    while(1)
    {
        line = readline("minishell$ ");
        if (!line )
        {
            free(line);
            break;
        }
        if (line[0] == '\0')
        {
            free(line);
            continue;
        }
        if (!line[0])
        {
            continue;
        }
        if (*line)
            add_history(line);
        cmd = ferst_s(line);
        if (cmd_syntax(cmd))
        {
            free_list(cmd);
            free(line);
            continue;
        }
        if (!i)
        {
           if (expand(cmd, env))
              {
                free(line);
                continue;
              }
           if (!cmd)
           {
               free(line);
               continue;
           }
           if (!split_cmd(cmd))
           {
               free(line);
               continue;
           }
           del_quote(cmd);
           tmp2 = cmd;
            // while (cmd)
            // {
            //     printf("content:[%s] - ", cmd->content);
            //     printf("type: [%c]\n", cmd->type);
            //     cmd = cmd->next;
            // }
            print_tree(parse_pipe(tmp2));
        }
        free(line);
        i = 0;
    }
    return (0);
}

//TODO  fix the single quote tokenzation 'ls  -ls'ls take it as [ls] [-ls] [ls] instead of [ls -lsls]