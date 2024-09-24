/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:05:03 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/24 18:01:58 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int		ft_word(char *str, int len, int *k)
{
	char hold;
	while (str[len] && ft_isspace(str[len]))
		len++;
	if (str[len] && !ft_isspace(str[len]))
		*k = len;
	while (str[len] && !ft_isspace(str[len]))
	{
		while (str[len] && (!ft_isspace(str[len]) && (str[len] != '"' && str[len] != '\'')))
			len++;
		if (str[len] == '"' || str[len] == '\'')
		{
			hold = str[len];
			len++;
			while (str[len] && str[len] != hold)
				len++;
			if (str[len] == hold)
				len++;
		}
	}
	return (len);
}

int		count_words(char *str)
{
	int	count;
	int i;
	int k;

	i = 0;
	k = 0;
	count = 0;
	while (str[i])
	{

		i = ft_word(str, i, &k);
		if (k == i)
			break ;
		count++;
		while (str[i] && ft_isspace(str[i]))
			i++;

	}
	return (count);
}

char	**ft_split(char *str)
{
	int j;
	char **arr;
	int i;
	int k;

	j = 0;
	i = 0;
	arr = ft_malloc(sizeof(char *) * (count_words(str) + 1));
	if (!arr)
		return (NULL);
	k = 0;
	while (str[i])
	{
		i = ft_word(str, i, &k);
		if (k == i)
			break ;
		arr[j] = ft_ft_substr(str, k, i - k);
		j++;
		while (str[i] && ft_isspace(str[i]))
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

