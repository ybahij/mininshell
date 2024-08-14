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
                printf("Syntax error unclosed quotes `%c'\n", quote);
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
    if (!tmp2)
    {
        printf("Syntax error near unexpected token `%s'\n", "newline");
        return (0);
    }
    if (cm_strchr("|<>o&", tmp2->type))
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
        return (printf("Syntax error near unexpected token '%s'\n", tmp->content), 1);
    while (tmp)
    {
        if (cm_strchr("|<>oh+&", tmp->type))
        {
            if (!pars_(tmp))
                return (1);
        }
        if (tmp->type == '"' || tmp->type == '\'')
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
        while (env[i][j] == str[j] && env[i][j] && str[j])
            j++;
        if (env[i][j] == '=' && !str[j])
        {
            free(str);
            str = ft_strdup(env[i] + j + 1);
            tmp = str;
            break;
        }
        i++;
    }
    return (tmp);
}

int appand_u(int *i, int j, char *content, int fd, char **env)
{
    char *tmp2;
    int len;
    int k;
    int d;
    int l;

    len = 0;
    l = 0;
    d = 0;
    k = *i;
    if (content[k] == '$' || !ft_isalnum(content[k]))
    {
        k++;
        *i = k;
        return (write (fd, &content[k - 1], 1));
    }
    while (content[k] && (ft_isalnum(content[k]) && content[k] != '$' && content[k] != '"' && content[k] != '\''))
        k++;
    tmp2 = cheak_env(ft_substr(content, j, k - j), env);
    if (tmp2)
    {
        len += write(fd, tmp2, ft_strlen(tmp2));
    }

    free(tmp2);
    *i = k;
    return (len);
}


int appand_in_fille(char *content, int fd, char **env)
{
    int len;
    int i;
    char hold;
    int j;

    i = 0;
    j = 0;
    len = 0;
    hold = 0;
    while (content[i])
    {
        if ((content[i] == '"' || content[i] == '\'') && hold == 0)
            hold = content[i];
        else if (content[i] == hold)
            hold = 0;
        if (hold != '\'' && content[i] == '$' && !cm_strchr("!@#$\%^&*()=+\\|[]{};:/?.", content[i + 1]))
        {
            i++;
            j = i;
            if (ft_isdigit(content[i]))
            {
                i++;
                continue;
            }
            len += appand_u(&j, i, content, fd, env);
            i = j;
        }
        else
        {
            len += write(fd, &content[i], 1);
            i++;
        }
    }
    return (len);
}

char *expand_w(char *content, char **env)
{
    char *tmp2;
    int fd[2];
    char fname[10];
    int rfd;
    int len;


    len = 0;
    pipe(fd);
    len = appand_in_fille(content, fd[1], env);
    close(fd[1]);
    rfd = fd[0];
    free(content);
    content = malloc(len + 2);
    read(fd[0], content, len);
    content[len] = '\0';
    close(fd[0]);
    return (content);
}

void    expand(lexer_t *cmd, char **env)
{
    lexer_t *tmp;
    int i = 0;
    int j = 0;
    char *tmp2;
    char *tmp3;

    while (cmd)
    {
        if (cm_strchr(cmd->content, '$'))
            cmd->content = expand_w(cmd->content, env);
        cmd = cmd->next;
    }
}

int ft_line(char *content)
{
    int i;
    int len;
    char  hold;

    i = 0;
    len = 0;
    while (content[i])
    {
        if (content[i] == '\'' && content[i] == '"')
        {
            hold = content[i];
            i++;
            while (content[i] && content[i] != hold)
            {
                len++;
                i++;
            }
        }
        if (content[i])
        {
            len++;
            i++;
        }
    }
    return (len);
}

int del_quote(lexer_t *cmd)
{
    int i;
    int j;
    char *tmp;
    char hold;

    if (cm_strchr("w|><", cmd->type))
        return (0);

    tmp = malloc(ft_line(cmd->content) + 1);
    if (!tmp)
        return (1);
    hold = 0;
    while(cmd)
    {
        i = 0;
        j = 0;
        while (cmd->content[i])
        {
            if (cmd->content[i] == '"' || cmd->content[i] == '\'')
            {
                hold = cmd->content[i];
                i++;
                while (cmd->content[i] && cmd->content[i] != hold)
                {
                    tmp[j] = cmd->content[i];
                    j++;
                    i++;
                }
                if (cmd->content[i])
                    i++;
            }
            if (cmd->content[i] && cmd->content[i] != '"' && cmd->content[i] != '\'')
            {
                tmp[j] = cmd->content[i];
                j++;
                i++;
            }
        }
        tmp[j] = '\0';
        free(cmd->content);
        cmd->content = tmp;
        cmd = cmd->next;
        }
        return (0);
}

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    lexer_t *cmd;
    lexer_t *tmp;
    int i = 0;

    while(1)
    {
        line = readline("mysh> ");
        if (!line )
        {
            free(line);
            break;
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
            free_(cmd);
            free(line);
            i=1;
        }
        if (!i)
        {
           expand(cmd, env);
           del_quote(cmd);
           tmp = cmd;
            while (tmp)
            {
                printf("cmd->content = [%s] = ", tmp->content);
                printf("cmd->type = %c\n", tmp->type);
                tmp = tmp->next;
            }
            while (cmd)
            {
                tmp = cmd->next;
                free(cmd->content);
                free(cmd);
                cmd = tmp;
            }
            free(line);
        }
        i = 0;
    }
    return (0);
}
