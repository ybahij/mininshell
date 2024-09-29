/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syantax1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:57:28 by youssef           #+#    #+#             */
/*   Updated: 2024/09/29 15:24:00 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheak_syntax(lexer_t *tmp)
{
	if (cm_strchr("|", tmp->type))
	{
		exit_s(2);
		printf(RED "minishell: syntax error near unexpected token `%s'\n"
			RESET, tmp->content);
		return (1);
	}
	return (0);
}

int	cmd_syntax(lexer_t *tmp, char **g_env, char *newline, lexer_t *tmp2)
{
	(void)g_env;
	if (!tmp)
		return (0);
	if (cheak_syntax(tmp))
		return (1);
	count_herdoc(tmp);
	while (tmp)
	{
		tmp2 = tmp;
		if (tmp->next && tmp->next->type == 'q')
		{
			if (!pars_quote(tmp->next->content))
				return (1);
		}
		tmp = syntax_error(tmp, newline);
		if (tmp != tmp2)
			continue ;
		if (tmp && !ft_strncmp(tmp->b_appand, "end_of_file", 11))
			return (1);
		else if (syntax_error_(tmp, newline))
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
				str = ft_strjoin(str, ft_ft_substr(tmp, i, 1));
				i++;
			}
		}
		else
			str = ft_strjoin(str, ft_ft_substr(tmp, i, 1));
		if (tmp[i])
			i++;
	}
	return (str);
}

char	*dellt_q(lexer_t *cmd, int i)
{
	char	*tmp;

	(void)i;
	if (!cmd->content)
		return (NULL);
	tmp = cmd->content;
	cmd->content = NULL;
	cmd->content = dellt_q_char(tmp);
	return (cmd->content);
}

int	del_quote(lexer_t *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (!cm_strchr("|<>h+", cmd->type))
		{
			if ((cmd->content[0] == '"' && cmd->content[1] == '"')
				|| (cmd->content[0] == '\'' && cmd->content[1] == '\''))
			{
				cmd = cmd->next;
				continue ;
			}
			if ((cmd->prev && cmd->prev->type != 'h') || !cmd->prev)
				cmd->content = dellt_q(cmd, 0);
		}
		cmd = cmd->next;
	}
	return (0);
}
