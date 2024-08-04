/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:24:17 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/06 23:24:29 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dest;

	dest = malloc ((ft_strlen(s1) + 1) * 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest [i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
