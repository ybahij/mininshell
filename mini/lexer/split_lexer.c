/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:05:15 by youssef           #+#    #+#             */
/*   Updated: 2024/08/31 17:33:52 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_digit(char *input, int k, int j, lexer_t **g_head)
{
	char	*str;

	str = ft_substr(input, k, j - k);
	printf(RED "minishell: syntax error near  `%s'\n" RESET, str);
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
	while (input[i] && !cm_strchr("|<>()", input[i]) && !is_space(input[i]))
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

int	parenthesis(char *input, int *i, lexer_t **head)
{
	lexer_t	*tmp;
	char	*str;
	int		j;

	j = *i;
	j++;
	while (input[j] && !cm_strchr("()", input[j]))
		j++;
	if (input[j] && cm_strchr("()", input[j]))
		j++;
	str = ft_substr(input, *i, j - *i);
	tmp = lexer(str, '(');
	ft_lstadd_back(head, tmp);
	*i = j;

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
				&& input[i + 1] == '|') || (input[i] == '(') || (input[i] == ')'))
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
