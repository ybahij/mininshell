/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:17:52 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/24 21:51:25 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*str_trimed(char *str, char const *s1, size_t *len, size_t *start)
{
	size_t	end;

	end = 0;
	while (end < *len)
		str[end++] = s1[(*start)++];
	str[end] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_check(s1[start], set))
		start++;
	if (start >= len)
		return ((char *)ft_calloc(1, sizeof(char)));
	end = len - 1;
	while (s1[end] && ft_check(s1[end], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	len = end - start + 1;
	return (str_trimed(str, s1, &len, &start));
}
