/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:47:04 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/26 13:58:47 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ldest;
	size_t	lsrc;

	if (!dstsize)
		return (ft_strlen(src));
	ldest = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (dstsize <= ldest)
		return (lsrc + dstsize);
	j = 0;
	i = ldest;
	while (src[j] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ldest + lsrc);
}
