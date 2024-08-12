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
            break;
        }
        i++;
    }
    return (str);
}

int appand_u(int *i, int j, char *content, int fd, char **env)
{
    char *tmp2;
    int len;
    int k;

    len = 0;
    k = *i;
    while (content[k] && ft_isalnum(content[k]) && content[k] != '$' && content[k] != '"' && content[k] != '\'')
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
        if (hold != '\'' && content[i] == '$')
        {
            i++;
            j = i;
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
    int fd;
    char fname[10];
    int rfd;
    int len;

    rfd  = open("/dev/random", O_RDONLY, 0644);
    read(rfd, &fname, 10);
    close(rfd);
    fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0644);
    len = appand_in_fille(content, fd, env);
    close(fd);
    fd = open(fname, O_RDONLY);
    free(content);
    content = malloc(len + 2);
    read(fd, content, len);
    content[len] = '\0';
    close(fd);
    unlink(fname);
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

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    lexer_t *cmd;
    lexer_t *tmp;
    int i = 0;

    while(1)
    {
        line = readline("mysh> ");
        if (!line)
            break;
        if (line)
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
            while (cmd)
            {
                tmp = cmd->next;
                printf("cmd->content = [%s] = ", cmd->content);
                printf("cmd->type = %c\n", cmd->type);
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