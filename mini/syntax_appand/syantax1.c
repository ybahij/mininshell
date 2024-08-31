/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syantax1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:57:28 by youssef           #+#    #+#             */
/*   Updated: 2024/08/31 22:09:17 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_pipe_(lexer_t *tmp, char *newline)
{
	if (!tmp->next)
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
			newline);
		return (0);
	}
	if (cm_strchr("|&o", tmp->next->type))
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
			tmp->next->content);
		return (0);
	}
	return (1);
}

int	cmd_syntax(lexer_t *tmp, char **g_env, char *newline)
{
	lexer_t	*tmp2;

	if (!tmp)
		return (0);
	if (cm_strchr("|o&", tmp->type))
		return (printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
				tmp->content), 1);
	count_herdoc(tmp);
	while (tmp)
	{
		tmp2 = tmp;
		tmp = syntax_error(tmp, g_env);
		if (!tmp)
			return (1);
		if (tmp != tmp2)
			continue ;
		else if (syntax_error_(tmp, g_env, newline))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*dellt_q_char(char *tmp)
{
	int		i;
	char	*str;
	char	hold;

	i = 0;
	str = NULL;
	while (tmp[i])
	{
		if (tmp[i] == '"' || tmp[i] == '\'')
		{
			hold = tmp[i];
			i++;
			while (tmp[i] && tmp[i] != hold)
			{
				str = ft_strjoin(str, ft_substr(tmp, i, 1));
				i++;
			}
		}
		else
			str = ft_strjoin(str, ft_substr(tmp, i, 1));
		if (tmp[i])
			i++;
	}
	return (str);
}

char	*dellt_q(lexer_t *cmd, int i)
{
	char	*tmp;
	char	hold;

	if (!cmd->content)
		return (NULL);
	tmp = cmd->content;
	cmd->content = NULL;
	cmd->content = dellt_q_char(tmp);
	return (cmd->content);
}

int	del_quote(lexer_t *cmd)
{
	int		i;
	int		j;
	char	*tmp;
	char	hold;

	while (cmd)
	{
		if (!cm_strchr("|<>oh+&(", cmd->type))
		{
			if ((cmd->prev && cmd->prev->type != 'h') || !cmd->prev)
				cmd->content = dellt_q(cmd, 0);
		}
		cmd = cmd->next;
	}
	return (0);
}
