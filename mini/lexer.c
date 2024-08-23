
#include "libft.h"

lexer_t *ft_lstlast(lexer_t *lst)
{
	while (lst != NULL)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void ft_lstadd_back(lexer_t **lst, lexer_t *new)
{
    lexer_t *last;

    if (*lst == NULL)
    {
        *lst = new;
    }
    else
    {
        last = ft_lstlast(*lst);
        last->next = new;
        new->prev = last;
    }
}

lexer_t *lexer(char *input, char type)
{
    lexer_t *head;
    head = malloc(sizeof(lexer_t));
    if (!head)
        return (NULL);
    head->content = ft_strdup(input);
    head->type = type;
    head->b_appand = NULL;
    head->next = NULL;
    head->prev = NULL;
    free(input);
    input = NULL;
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
    int j;
    lexer_t *tmp;
    char qoute_type;

    j = *k;
    qoute_type = input[j];
    j++;
    while (input[j] && input[j] != qoute_type)
        j++;
    while (input[j] && !is_space(input[j]))
        j++;
    tmp = lexer(ft_substr(input, *k, j - *k), 'q');
    ft_lstadd_back(head, tmp);
    if (input[j])
        j++;
    *k = j;
    return (0);
}

int redir_o(char *input, int *j, lexer_t **head)
{
    lexer_t *tmp;
    int i;

    i = *j;
    if (input[i] == '>')
    {
        if (input[i + 1] == '>')
        {
            tmp = lexer(ft_substr(input, i, 2), '+');
            ft_lstadd_back(head, tmp);
            i += 2;
        }
        else
        {
            tmp = lexer(ft_substr(input, i, 1), '>');
            ft_lstadd_back(head, tmp);
            i++;
        }
    }
    *j = i;
    return (0);
}

int redir_i(char *input, int *j, lexer_t **head)
{
    lexer_t *tmp;
    int i;

    i = *j;
    if (input[i] == '<')
    {
        if (input[i + 1] == '<')
        {
            tmp = lexer(ft_substr(input, i, 2), 'h');
            ft_lstadd_back(head, tmp);
            i += 2;
        }
        else
        {
            tmp = lexer(ft_substr(input, i, 1), '<');
            ft_lstadd_back(head, tmp);
            i++;
        }
    }
    *j = i;
    return (0);
}

int r_pipe(char *input, int *j, lexer_t **head)
{
    lexer_t *tmp;
    int i;

    i = *j;
    if (input[i] == '|')
    {
        if (input[i + 1] && input[i + 1] == '|')
        {
            tmp = lexer(ft_substr(input, i, 2), 'o');
            ft_lstadd_back(head, tmp);
            i += 2;
        }
        else
        {
            tmp = lexer(ft_substr(input, i, 1), '|');
            ft_lstadd_back(head, tmp);
            i++;
        }
    }
    if (input[i] == '<')
        redir_i(input, &i, head);
    if (input[i] == '>')
        redir_o(input, &i, head);
    *j = i;
    return (0);
}

int n_cmd(char *input, int *j, lexer_t **head)
{
    lexer_t *tmp;
    char t;
    int i;
    char holder;

    i = *j;
    t = 'w';
    while (input[i] && !cm_strchr("|<>", input[i]) && !is_space(input[i]))
    {
        if (input[i] == '&' && input[i + 1] == '&')
            break;
        if (input[i] == '\'' || input[i] == '\"')
        {
            holder = input[i];
            t = 'q';
            if (input[i + 1])
                i++;
            while (input[i] && input[i] != holder)
                i++;
        }
        if (input[i])
            i++;
    }
    char *str = ft_substr(input, *j, i - *j);
    tmp = lexer(str, t);
    ft_lstadd_back(head, tmp);
    *j = i;
    return (0);
}

int and_or(char *input, int *i, lexer_t **head)
{
    lexer_t *tmp;
    int j;

    j = *i;
    if (input[j] == '&' && input[j + 1] == '&')
    {
        tmp = lexer(ft_substr(input, j, 2), '&');
        ft_lstadd_back(head, tmp);
        j += 2;
    }
    *i = j;
    return (0);
}

lexer_t *ferst_s(char *input)
{
    lexer_t *head;
    int i;
    int j;
    lexer_t *tmp;

    i = 0;
    head = NULL;
    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;
        if ((input[i] == '&' && input[i + 1] == '&'))
            and_or(input, &i, &head);
	    else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
            r_pipe(input, &i, &head);
	    else if (input[i] && !is_space(input[i]) && input[i] != '\n' && !cm_strchr("|<>", input[i]))
            n_cmd(input, &i, &head);
    }
    return (head);
}

