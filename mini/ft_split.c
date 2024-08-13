/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:05:03 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/23 09:57:17 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>

static int	ft_count_words(const char *str, char c)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] != c)
        {
            count++;
            while (str[i] && str[i] != c)
                i++;
        }
        else
        {
            count++;
            i++;
        }
    }
    return (count);
}

static char	*ft_strndup(const char *s1, int n)
{
    char	*dup;
    int		i;

    dup = (char *)malloc(sizeof(char) * (n + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n)
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}


lexer_t *ft_join(char **split, char c)
{
	int i = 0;
	int j = 0;
	int k = 0;
	lexer_t *new_split;
	lexer_t *tmp;
	new_split = NULL;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == c)
			{
				tmp = malloc(sizeof(lexer_t));
				tmp->content = ft_strndup(split[i] + k, j - k);
				tmp->next = NULL;
				if (!new_split)
					new_split = tmp;
				else
					ft_lstadd_back(&new_split, tmp);
				k = j + 1;
			}
			j++;
		}
		i++;
	}
    return (NULL);
}

void	free_split(char **split)
{
	int i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int ft_lstsize(lexer_t *lst)
{
	int i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}


char **ft_join_split(lexer_t *new_split)
{
	int i = 0;
	int j = 0;
	char **split;
	lexer_t *tmp;
	split = malloc(sizeof(char *) * (ft_lstsize(new_split) + 1));
	if (!split)
		return (NULL);
	tmp = new_split;
	while (tmp)
	{
		split[j] = tmp->content;
		j++;
		tmp = tmp->next;
	}
	split[j] = NULL;
	return (split);
}

char		**ft_split(const char *s, char c)
{
    char	**split;
	lexer_t *new_split;
    int		i;
    int		j;
    int		k;

    if (!s)
        return (NULL);
    split = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
    if (!split)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] != c)
        {
            k = 0;
            while (s[i + k] && s[i + k] != c)
                k++;
            split[j++] = ft_strndup(s + i, k);
            i += k;
        }
        else
        {
            split[j++] = ft_strndup(s + i, 1);
            i++;
        }
    }
    split[j] = NULL;
	new_split = ft_join(split, c);
	free_split(split);
	split = ft_join_split(new_split);
    return (split);
}