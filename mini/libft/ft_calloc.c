/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:42:53 by ybahij            #+#    #+#             */
/*   Updated: 2024/08/30 16:50:38 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*src;

	total_size = count * size;
	src = ft_malloc(total_size);
	if (src == NULL)
		return (NULL);
	ft_bzero(src, total_size);
	return (src);
}
