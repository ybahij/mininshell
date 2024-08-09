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

int expand_w(lexer_t *cmd, char **env)
{
    char *tmp2;
    char *tmp3;
    int i = 0;
    int j = 0;
    i = 0;
    while (env[i])
    {
        j = 0;
        while (env[i][j] == cmd->content[j + 1] && env[i][j] && cmd->content[j + 1])
            j++;
        if (env[i][j] == '=')
        {
            tmp2 = ft_strdup(&cmd->content[j + 1]);
            tmp3 = ft_strjoin(env[i] + j + 1, tmp2);
            free(cmd->content);
            cmd->content = tmp3;
            free(tmp2);
            break;
        }
        i++;
    }
    return (1);
}

int expand_q(lexer_t *cmd, char **env)
{
    char *tmp2;
    char *tmp3;
    int i = 0;
    int j = 0;
    i = 0;
    while (env[i])
    {
        if 
    }
    return (1);
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
        {
            if (cmd->type == 'w')
                expand_w(cmd, env);
            if (cmd->type == '"' || cmd->type == '\'')
                expand_q(cmd, env);
            }
        cmd = cmd->next;
    }
}

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    lexer_t *cmd;
    lexer_t *tmp;
    int i = 0;


    int j = 0;
    // while (env[j])
    // {
    //     printf("%s\n",env[j]);
    //     j++;
    // }
    while(1)
    {
        line = readline("mysh> ");
        cmd = ferst_s(line);
        if (cmd_syntax(cmd))
        {
            free_(cmd);
            free(line);
            i=1;
        }
        expand(cmd, env);
        if (!i)
        {
            while (cmd)
            {
                tmp = cmd->next;
                printf("cmd->content = [%s] = ", cmd->content);
                printf("cmd->type = %c\n", cmd->type);
                free(cmd);
                cmd = tmp;
            }
            free(line);
        }
        i = 0;
    }
    return (0);
}