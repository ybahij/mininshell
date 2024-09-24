/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:47:40 by youssef           #+#    #+#             */
/*   Updated: 2024/09/24 11:00:12 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	and_or(char *input, int *i, lexer_t **head)
{
	lexer_t	*tmp;
	int		j;

	j = *i;
	if (cm_strchr("()", input[j]))
	{
		parenthesis(input, &j, head);
		*i = j;
		return (0);
	}
	if (input[j] == '|' && input[j + 1] == '|')
	{
		tmp = lexer(ft_ft_substr(input, j, 2), 'o');
		if (!tmp)
			return (1);
		ft_lstadd_back(head, tmp);
		j += 2;
	}
	if (input[j] == '&' && input[j + 1] == '&')
	{
		tmp = lexer(ft_ft_substr(input, j, 2), '&');
		if (!tmp)
			return (1);
		ft_lstadd_back(head, tmp);
		j += 2;
	}
	*i = j;
	return (0);
}
