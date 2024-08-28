
#include "minishell.h"



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
        if (!cmd)
            continue;
        if (cmd_syntax(cmd, env))
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
            print_tree(parse_and(cmd));
        }
        free(line);
        i = 0;
    }
    return (0);
}
