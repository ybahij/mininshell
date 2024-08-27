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

#include "../minishell.h"

void	cm_strcpy(char *dest, char *src,  int *j)
{
	int i;
	int k;

	i = 0;
	k = *j;
	while (src[i])
	{
		dest[k] = src[i];
		i++;
		k++;
	}
	*j = k;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int 	i;
	char	*str;

	i = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	if (s1)
	{
		cm_strcpy(str, s1, &i);
		free(s1);
	}
	if (s2)
	{
		cm_strcpy(str, s2, &i);
		free(s2);
	}
	str[i] = '\0';
	return (str);
}
