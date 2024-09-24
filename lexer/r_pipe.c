/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:48:28 by youssef           #+#    #+#             */
/*   Updated: 2024/09/24 11:00:55 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheak_digit(char *input, int *i)
{
	int		j;
	char	hold;
	int		k;

	j = *i;
	hold = input[j];
	j++;
	k = j;
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
			exit_s(2);
			return (printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
					ft_substr(input, k, j - k)), 1);
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
			if (!tmp)
				return (1);
			ft_lstadd_back(head, tmp);
			i += 2;
		}
		else
		{
			if (cheak_digit(input, &i))
				return (1);
			tmp = lexer(ft_substr(input, i, 1), '>');
			if (!tmp)
				return (1);
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
			tmp = lexer(ft_ft_substr(input, i, 2), 'h');
			if (!tmp)
				return (1);
			ft_lstadd_back(head, tmp);
			i += 2;
		}
		else
		{
			if (cheak_digit(input, &i))
				return (1);
			tmp = lexer(ft_ft_substr(input, i, 1), '<');
			if (!tmp)
				return (1);
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
		{
			return (1);
		}
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
	lexer_t *tmp;
	int i;

	i = *j;
	if (input[i] == '|')
	{
		tmp = lexer(ft_ft_substr(input, i, 1), '|');
		if (!tmp)
			return (1);
		ft_lstadd_back(head, tmp);
		i++;
	}
	if (input[i] == '<' || input[i] == '>')
	{
		if (redir(input, &i, head))
		{
			return (1);
		}
	}
	*j = i;
	return (0);
}