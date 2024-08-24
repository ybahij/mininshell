
#include "minishell.h"

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

void    free_digit(char *input, int k, int j, lexer_t **g_head)
{
    char *str;

    str = ft_substr(input, k, j - k);
    free_list(*g_head);
    printf(RED"minishell: syntax error near  `%s'\n"RESET, str);
    free(str);
    free(input);
}

int cheak_digit(char *input, int *i , lexer_t **g_head)
{
    int j;
    int k;
    char hold;

    j = *i;
    hold = input[j];
    j++;
    if (input[j] == hold)
        j++;
    while (input[j] && is_space(input[j]))
        j++;
    k = j;
    if (input[j] && ft_isdigit(input[j]))
    {
        while (input[j] && ft_isdigit(input[j]))
            j++;
        if (input[j] && cm_strchr("<>", input[j]))
        {
            free_digit(input, k, j, g_head);
            return (1);
        }
    }
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
            if (cheak_digit(input, &i, head))
                return (1);
            tmp = lexer(ft_substr(input, i, 2), '+');
            ft_lstadd_back(head, tmp);
            i += 2;
        }
        else
        {
            if (cheak_digit(input, &i, head))
                return (1);
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
            if (cheak_digit(input, &i, head))
                return (1);
            tmp = lexer(ft_substr(input, i, 2), 'h');
            ft_lstadd_back(head, tmp);
            i += 2;
        }
        else
        {
            if (cheak_digit(input, &i, head))
                return (1);
            tmp = lexer(ft_substr(input, i, 1), '<');
            ft_lstadd_back(head, tmp);
            i++;
        }
    }
    *j = i;
    return (0);
}

int  redir(char *input, int *i, lexer_t **head)
{
    int j;

    j = *i;
    if (input[j] == '<')
    {
        if (redir_i(input, &j, head))
            return (1);
    }
    if (input[j] == '>')
    {
        if (redir_o(input, &j, head))
            return (1);
    }
    *i = j;
    return (0);
}

int r_pipe(char *input, int *j, lexer_t **head)
{
    lexer_t *tmp;
    int i;

    i = *j;
    if (input[i] == '|')
    {
        tmp = lexer(ft_substr(input, i, 1), '|');
        ft_lstadd_back(head, tmp);
        i++;
    }
    if (input[i] == '<' || input[i] == '>')
    {
        if (redir(input, &i, head))
            return (1);
    }
    *j = i;
    return (0);
}

int cmd_lexer(char *input, int *j, lexer_t **head, char t, int i)
{
    lexer_t *tmp;

    char *str = ft_substr(input, *j, i - *j);
    tmp = lexer(str, t);
    ft_lstadd_back(head, tmp);
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
    return (cmd_lexer(input, j, head, t, i));
}

int and_or(char *input, int *i, lexer_t **head)
{
    lexer_t *tmp;
    int j;

    j = *i;
    if (input[j] == '|' && input[j + 1] == '|')
    {
        tmp = lexer(ft_substr(input, j, 2), 'o');
        ft_lstadd_back(head, tmp);
        j += 2;
    }
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
        if ((input[i] == '&' && input[i + 1] == '&') || (input[i] == '|' && input[i + 1] == '|'))
            and_or(input, &i, &head);
	    else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
        {
            if (r_pipe(input, &i, &head))
                return (NULL);
        }
	    else if (input[i] && !is_space(input[i]) && input[i] != '\n' && !cm_strchr("|<>", input[i]))
            n_cmd(input, &i, &head);
    }
    return (head);
}

