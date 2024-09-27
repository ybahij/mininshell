/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:45:48 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/27 23:49:32 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;

	i = 1;
	if (n == 0)
		return (1);
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != n || ft_strlen(s2) != n)
		return (1);
	while (i < n)
	{
		if (*s1 != *s2)

			break;
		s1++;
		s2++;
		i++;
	}
	return (*s1 - *s2);
}
