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

#include"libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i))
		{
			count++;
			while (*(s + i) && !cm_strchr(" \t\v\f\r", *(s + i)))
				i++;
		}
		else if (cm_strchr(" \t\v\f\r", *(s + i)))
			i++;
	}
	return (count);
}

static size_t	get_word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && !cm_strchr(" \t\v\f\r", *(s + i)))
		i++;
	return (i);
}

static void	free_array(size_t i, char **array)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(*(array + j));
		j++;
	}
	free(array);
}

static char	**split(char const *s, char c, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && cm_strchr(" \t\v\f\r", *(s + i)))
			j++;
		*(array + i) = ft_substr(s, j, get_word_len(&*(s + j), c));
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		while (*(s + j) && !cm_strchr(" \t\v\f\r", *(s + i)))
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split(s, c, array, words);
	return (array);
}

int main()
{
    char **str = ft_split("  ls | la < lk| ", ' ');
    int i = 0;
    while (i)
    {    
        printf ("str[%d] = %s\n", i, str[i]);
        i++;}
}