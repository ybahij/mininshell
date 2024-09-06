/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:48:28 by youssef           #+#    #+#             */
/*   Updated: 2024/09/06 15:35:39 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheak_digit(char *input, int *i)
{
	int		j;
	char	hold;

	j = *i;
	hold = input[j];
	j++;
	if (input[j] == hold)
		j++;
	while (input[j] && is_space(input[j]))
		j++;
	if (input[j] && ft_isdigit(input[j]))
	{
		while (input[j] && ft_isdigit(input[j]))
			j++;
		if (input[j] && cm_strchr("<>", input[j]))
		{
			return (1);
		}
	}
	return (0);
}

int	redir_o(char *input, int *j, lexer_t **head)
{
	lexer_t	*tmp;
	int		i;

	i = *j;
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			if (cheak_digit(input, &i))
				return (1);
			tmp = lexer(ft_substr(input, i, 2), '+');
			ft_lstadd_back(head, tmp);
			i += 2;
		}
		else
		{
			if (cheak_digit(input, &i))
				return (1);
			tmp = lexer(ft_substr(input, i, 1), '>');
			ft_lstadd_back(head, tmp);
			i++;
		}
	}
	*j = i;
	return (0);
}

int	redir_i(char *input, int *j, lexer_t **head)
{
	lexer_t	*tmp;
	int		i;

	i = *j;
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			if (cheak_digit(input, &i))
				return (1);
			tmp = lexer(ft_substr(input, i, 2), 'h');
			ft_lstadd_back(head, tmp);
			i += 2;
		}
		else
		{
			if (cheak_digit(input, &i))
				return (1);
			tmp = lexer(ft_substr(input, i, 1), '<');
			ft_lstadd_back(head, tmp);
			i++;
		}
	}
	*j = i;
	return (0);
}

int	redir(char *input, int *i, lexer_t **head)
{
	int	j;

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

int	r_pipe(char *input, int *j, lexer_t **head)
{
	lexer_t	*tmp;
	int		i;

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