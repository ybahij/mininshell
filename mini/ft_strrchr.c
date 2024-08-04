/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:39:14 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/11 07:03:26 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	len;

	len = 0;
	while (s[len])
		len++;
	if ((char)c == '\0')
		return ((char *)s + len);
	i = len - 1;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
