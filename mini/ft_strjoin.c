/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:20 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/11 02:27:26 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	tlen;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	tlen = ft_strlen(s1) + ft_strlen(s2);
	tab = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s1, ft_strlen(s1) + 1);
	ft_strlcpy(tab + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (tab);
}
