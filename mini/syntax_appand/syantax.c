/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syantax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:49:59 by youssef           #+#    #+#             */
/*   Updated: 2024/08/28 17:27:45 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_quote(char *content)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			quote = content[i];
			i++;
			while (content[i] && content[i] != quote)
				i++;
			if (content[i] != quote)
			{
				printf(RED "minishell: syntax error unclosed quotes `%c'\n" RESET,
					quote);
				return (0);
			}
		}
		if (content[i])
			i++;
	}
	return (1);
}

int	pars_(lexer_t *tmp)
{
	lexer_t	*tmp2;

	tmp2 = tmp->next;
	if (!tmp2)
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
			"newline");
		return (0);
	}
	if (cm_strchr("><+h|&o", tmp2->type))
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
			tmp2->content);
		return (0);
	}
	if (cm_strchr("|&o", tmp->type) && cm_strchr("|&o", tmp2->type))
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
			tmp2->content);
		return (0);
	}
	return (1);
}

int	syntax_error_(lexer_t *tmp, char **g_env)
{
	if (cm_strchr("<>oh+&", tmp->type))
	{
		if (!pars_(tmp))
			return (1);
	}
	if (tmp->type == '|')
	{
		if (!pars_pipe_(tmp))
			return (1);
	}
	else if (tmp->type == 'q')
	{
		if (!pars_quote(tmp->content))
			return (1);
	}
	return (0);
}

char	*quote_(char *content)
{
	char	*str;

	str = content;
	content = dellt_q_char(content);
	free(str);
	if (!content)
		return (ft_strdup(""));
	return (content);
}

lexer_t	*syntax_error(lexer_t *tmp, char **g_env)
{
	if (tmp->prev && tmp->prev->type == 'h')
	{
		if (tmp->type == 'w' || tmp->type == 'q')
			return (tmp->next);
	}
	else if (tmp->type == 'h' && tmp->next)
	{
		if (tmp->next->type == 'w' || tmp->next->type == 'q')
		{
			heandal_herdoc(tmp, g_env);
			return (tmp = tmp->next);
		}
	}
	return (tmp);
}
