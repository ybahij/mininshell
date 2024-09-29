/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:56:18 by youssef           #+#    #+#             */
/*   Updated: 2024/09/29 13:38:36 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

lexer_t	*split_1(lexer_t *head, char **str, int i)
{
	lexer_t	*tmp;
	lexer_t	*tmpl;

	tmp = head->next;
	head->content = str[0];
	head->next = NULL;
	i = 1;
	while (str[i])
	{
		tmpl = lexer(str[i], 'w');
		ft_lstadd_back(&head, tmpl);
		i++;
	}
	tmpl = ft_lstlast(head);
	tmpl->next = tmp;
	if (tmp)
		tmp->prev = tmpl;
	return (tmp);
}

lexer_t	*spilt_(lexer_t *head, int i)
{
	char	**str;

	i = 0;
	str = ft_split(head->content);
	if (!head || !str)
		return (NULL);
	while (str[i])
		i++;
	if (i > 1)
	{
		if (head->prev && cm_strchr("+><", head->prev->type))
		{
			printf(RED "minishell: %s: ambiguous redirect\n" RESET,
				head->b_appand);
			head->b_appand = NULL;
			head->b_appand = ft_ft_strdup("ambiguous redirect");
			exit_s(1);
			return (head);
		}
		return (split_1(head, str, i));
	}
	head->content = ft_ft_strdup(str[0]);
	return (head->next);
}

int	split_cmd(lexer_t *head)
{
	lexer_t	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->content && cm_strchr(tmp->content, ' '))
		{
			tmp = spilt_(tmp, 0);
			if (g_data.fall)
				return (0);
			if (tmp && !ft_strncmp(tmp->b_appand, "ambiguous redirect", 18))
			{
				tmp->b_appand = NULL;
				return (0);
			}
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

