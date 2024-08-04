/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:10:45 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/16 14:37:27 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tab;
	int		count;

	count = 0;
	if (lst == NULL)
		return (0);
	tab = lst;
	while (tab != NULL)
	{
		count++;
		tab = tab->next;
	}
	return (count);
}
