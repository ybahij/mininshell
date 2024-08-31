/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:47:40 by youssef           #+#    #+#             */
/*   Updated: 2024/08/30 01:39:19 by youssef          ###   ########.fr       */
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
