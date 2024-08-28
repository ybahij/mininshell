/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:56:18 by youssef           #+#    #+#             */
/*   Updated: 2024/08/28 17:29:31 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

lexer_t	*split_1(lexer_t *head, char **str, int i)
{
	lexer_t	*tmp;
	lexer_t	*tmpl;

	tmp = head->next;
	free(head->content);
	head->content = str[0];
	head->next = NULL;
	i = 1;
	while (str[i])
	{
		tmpl = lexer(str[i], 'w');
		ft_lstadd_back(&head, tmpl);
		i++;
	}
	free(str);
	tmpl = ft_lstlast(head);
	tmpl->next = tmp;
	if (tmp)
		tmp->prev = tmpl;
	return (tmp);
}

lexer_t	*spilt_(lexer_t *head, int i)
{
	char	**str;
	char	*tmp;

	i = 0;
	if (!head || !(str = ft_split(head->content)))
		return (free_list(head), NULL);
	while (str[i])
		i++;
	if (i > 1)
	{
		if (head->prev && cm_strchr("+><", head->prev->type))
		{
			printf(RED "minishell: %s: ambiguous redirect\n" RESET,
				head->b_appand);
			free(head->b_appand);
			head->b_appand = NULL;
			head->b_appand = ft_strdup("ambiguous redirect");
			return (free_array(str), head);
		}
		return (split_1(head, str, i));
	}
	tmp = head->content;
	head->content = ft_strdup(str[0]);
	free(tmp);
	return (free_array(str), head->next);
}

int	split_cmd(lexer_t *head)
{
	lexer_t *tmp = head;

	while (tmp)
	{
		if (tmp->content && cm_strchr(tmp->content, ' ') && tmp->prev
			&& tmp->prev->type != 'h')
		{
			tmp = spilt_(tmp, 0);
			if (tmp && !ft_strncmp(tmp->b_appand, "ambiguous redirect", 18))
			{
				free(tmp->b_appand);
				tmp->b_appand = NULL;
				return (free_list(head), 0);
			}
		}
		else
			tmp = tmp->next;
	}
	return (1);
}
