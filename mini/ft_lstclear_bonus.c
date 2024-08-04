/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:20:41 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/17 17:53:38 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tab;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tab = (*lst)-> next;
		ft_lstdelone(*lst, del);
		(*lst) = tab;
	}
}
