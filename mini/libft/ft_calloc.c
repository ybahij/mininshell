/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:42:53 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/17 17:01:20 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*src;

	total_size = count * size;
	src = malloc(total_size);
	if (src == NULL)
		return (NULL);
	ft_bzero(src, total_size);
	return (src);
}
