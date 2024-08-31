/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:24:17 by ybahij            #+#    #+#             */
/*   Updated: 2024/08/30 16:51:05 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dest;

	if (!s1)
		return (ft_strdup(""));
	dest = ft_malloc ((ft_strlen(s1) + 1) * 1);
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
