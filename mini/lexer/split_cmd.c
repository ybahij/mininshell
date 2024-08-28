/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:50:34 by youssef           #+#    #+#             */
/*   Updated: 2024/08/28 14:52:35 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_digit(char *input, int k, int j, lexer_t **g_head)
{
	char	*str;

	str = ft_substr(input, k, j - k);
	free_list(*g_head);
	printf(RED "minishell: syntax error near  `%s'\n" RESET, str);
	free(str);
	free(input);
}

int	cmd_lexer(char *input, int *j, lexer_t **head, char t, int i)
{
	lexer_t	*tmp;
	char	*str;

	str = ft_substr(input, *j, i - *j);
	tmp = lexer(str, t);
	ft_lstadd_back(head, tmp);
	*j = i;
	return (0);
}

int	n_cmd(char *input, int *j, lexer_t **head)
{
	lexer_t	*tmp;
	char	t;
	int		i;
	char	holder;

	i = *j;
	t = 'w';
	while (input[i] && !cm_strchr("|<>", input[i]) && !is_space(input[i]))
	{
		if (input[i] == '&' && input[i + 1] == '&')
			break ;
		if (input[i] == '\'' || input[i] == '\"')
		{
			holder = input[i];
			t = 'q';
			if (input[i + 1])
				i++;
			while (input[i] && input[i] != holder)
				i++;
		}
		if (input[i])
			i++;
	}
	return (cmd_lexer(input, j, head, t, i));
}

lexer_t	*ferst_s(char *input)
{
	lexer_t	*head;
	int		i;
	int		j;
	lexer_t	*tmp;

	i = 0;
	head = NULL;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if ((input[i] == '&' && input[i + 1] == '&') || (input[i] == '|'
				&& input[i + 1] == '|'))
			and_or(input, &i, &head);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (r_pipe(input, &i, &head))
				return (NULL);
		}
		else if (input[i] && !is_space(input[i]) && input[i] != '\n'
			&& !cm_strchr("|<>", input[i]))
			n_cmd(input, &i, &head);
	}
	return (head);
}