/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:04:55 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/17 21:49:32 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*src;
	char	uc;
	size_t	i;

	i = 0;
	uc = (char)c;
	src = (char *)s;
	while (i < n)
	{
		if (src[i] == uc)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
