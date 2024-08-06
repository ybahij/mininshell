
#include "libft.h"

lexer_t *ft_lstlast(lexer_t *lst)
{
    if (lst == NULL)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void	ft_lstadd_back(lexer_t **lst, lexer_t *new)
{
    lexer_t	*last_node;

    last_node = ft_lstlast(*lst);
    if (*lst)
        last_node -> next = new;
    else
        *lst = new;
}

lexer_t *lexer(char *input, char type)
{
    lexer_t *head;
    head = malloc(sizeof(lexer_t));
    if (!head)
        return (NULL);
    head->content = input;
    head->type = type;
    head->next = NULL;

    return (head);  
}

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int    qoute(int *k, char *input, lexer_t **head)
{
    char qoute_type;
    lexer_t *tmp;
    int i;
    int j;

    j = 0;
    i = *k;
    if (input[i] == '"' || input[i] == '\'')
        {
            qoute_type = input[i];
            j = i;
            i++;
            while (input[i] && input[i] != qoute_type)
                i++;
            if (input[i] == qoute_type && (is_space(input[i + 1]) || input[i + 1] == '|' || input[i + 1] == '>' || input[i + 1] == '<' || !input[i + 1]))
            {
                i++;
                tmp = lexer(ft_substr(input, j, i - j), 'q');
                ft_lstadd_back(head, tmp);
            }
            else if (input[i] == qoute_type && (!is_space(input[i + 1] && input[i + 1] != '|' && input[i + 1] != '>' && input[i + 1] != '<')))
            {
                while (input[i] && (!is_space(input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<')))
                    i++;
                tmp = lexer(ft_substr(input, j, i - j), 'q');
                ft_lstadd_back(head, tmp);
                i++;
            }
        }
    *k = i;
    return (i);
}   
lexer_t *ferst_s(char *input)
{
    int i;
    int j;
    lexer_t *head;
    lexer_t *tmp;

    char qoute_type;
    head = NULL;
    i = -1;
    j = 0;
    while (input[++i])
    {
        while (is_space(input[i]) && input[i])
            i++;
        if (input[i] == '"' || input[i] == '\'')
            qoute(&i, input, &head);
        if (input[i] == '|')
        {
            tmp = lexer("|", '|');
            ft_lstadd_back(&head, tmp);
            i++;
        }
        else if (input[i] == '>')
        {
            if (input[i + 1] == '>')
            {
                tmp = lexer(">>", '>');
                ft_lstadd_back(&head, tmp);
                i++;
            }
            else
            {
                tmp = lexer(">", '>');
                ft_lstadd_back(&head, tmp);
                i++;
            }
        }
        else if (input[i] == '<')
        {
            if (input[i + 1] == '<')
            {
                tmp = lexer("<<", 'H');
                ft_lstadd_back(&head, tmp);
                i++;
            }
            else
            {
                tmp = lexer("<", '<');
                ft_lstadd_back(&head, tmp);
            }
        }
        else if (!is_space(input[i]))
        {
            while (is_space(input[i]))
                i++;
            if (!input[i])
                break;
            j = i;
            while (input[i] && (!is_space(input[i]) && input[i] != '|' && input[i] != '>' && input[i] != '<'))
                i++;
            tmp = lexer(ft_substr(input, j, i - j), 'w');
            ft_lstadd_back(&head, tmp);
            while (is_space(input[i]) && input[i])
                i++;
            if ((input[i] == '|' || input[i] == '>' || input[i] == '<'))
               i--;
        }
    }
    return (head);
}

