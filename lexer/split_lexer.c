/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:05:15 by youssef           #+#    #+#             */
/*   Updated: 2024/09/24 11:01:42 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd__(int *j, char *input, char *t, char holder)
{
	int	i;

	i = *j;
	while (input[i] && !cm_strchr("|<>()", input[i]) && !is_space(input[i]))
	{
		if (input[i] == '&' && input[i + 1] == '&')
			break ;
		if (input[i] == '\'' || input[i] == '\"')
		{
			holder = input[i];
			*t = 'q';
			if (input[i + 1])
				i++;
			while (input[i] && input[i] != holder)
				i++;
		}
		if (input[i])
			i++;
	}
	*j = i;
}

int	n_cmd(char *input, int *j, lexer_t **head)
{
	lexer_t	*tmp;
	char	t;
	int		i;
	char	holder;
	char	*str;

	i = *j;
	t = 'w';
	holder = 0;
	cmd__(&i, input, &t, holder);
	str = ft_ft_substr(input, *j, i - *j);
	if (!str)
		return (1);
	tmp = lexer(str, t);
	if (!tmp)
		return (1);
	ft_lstadd_back(head, tmp);
	*j = i;
	return (0);
}

int	parenthesis(char *input, int *i, lexer_t **head)
{
	lexer_t	*tmp;
	char	*str;
	int		j;

	j = *i;
	j++;
	while (input[j] && !cm_strchr("()", input[j]))
		j++;
	if (input[j] && cm_strchr("()", input[j]))
		j++;
	str = ft_ft_substr(input, *i, j - *i);
	if (!str)
		return (1);
	tmp = lexer(str, '(');
	if (!tmp)
		return (1);
	ft_lstadd_back(head, tmp);
	*i = j;
	return (0);
}

lexer_t	*ferst_s(char *input)
{
	lexer_t	*head;
	int		i;

	i = 0;
	head = NULL;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if ((input[i] == '&' && input[i + 1] == '&') || (input[i] == '|'
				&& input[i + 1] == '|') || (input[i] == '(')
			|| (input[i] == ')'))
		{	
			if(and_or(input, &i, &head))
				return (NULL);
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (r_pipe(input, &i, &head))
				return (NULL);
		}
		else if (input[i] && !is_space(input[i]) && input[i] != '\n'
			&& !cm_strchr("|<>", input[i]))
			if (n_cmd(input, &i, &head))
				return (NULL);
	}
	return (head);
}
