/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:42:29 by youssef           #+#    #+#             */
/*   Updated: 2024/08/28 14:52:24 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

lexer_t	*ft_lstlast(lexer_t *lst)
{
	while (lst != NULL)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(lexer_t **lst, lexer_t *new)
{
	lexer_t	*last;

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

lexer_t	*lexer(char *input, char type)
{
	lexer_t	*head;

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

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	qoute(int *k, char *input, lexer_t **head)
{
	int		j;
	lexer_t	*tmp;
	char	qoute_type;

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








