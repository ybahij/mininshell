/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:50:59 by youssef           #+#    #+#             */
/*   Updated: 2024/08/28 17:05:41 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*herdoc_appand1(char *content, char **g_env, char *str, int *i)
{
	int		j;
	char	*tmp2;
	int		k;

	j = *i;
	j++;
	k = j;
	while (content[j] && (ft_isalnum(content[j])))
		j++;
	tmp2 = cheak_env(ft_substr(content, k, j - k), g_env);
	if (tmp2)
		str = ft_strjoin(str, tmp2);
	*i = j;
	return (str);
}

void	count_herdoc(lexer_t *tmp)
{
	int		i;
	lexer_t	*tmp2;

	i = 0;
	tmp2 = tmp;
	while (tmp)
	{
		if (tmp->type == 'h')
		{
			if (!tmp->next || tmp->next->type != 'w')
				return ;
			i++;
		}
		tmp = tmp->next;
	}
	if (i > 16)
	{
		free_list(tmp);
		exit(1);
	}
}

char	*herdoc_appand(char *content, char type, char **g_env)
{
	char *str;
	int i;

	i = 0;
	str = NULL;
	if (type != 'w' || !cm_strchr(content, '$'))
		return (content);
	while (content[i])
	{
		if (content[i] == '$' && !cm_strchr("!@#\%^&*$()=+\\|[]{};\"\':/?.",
				content[i + 1]))
			str = herdoc_appand1(content, g_env, str, &i);
		else
		{
			str = ft_strjoin(str, ft_substr(content, i, 1));
			i++;
		}
	}
	free(content);
	return (str);
}

void	heandal_herdoc(lexer_t *tmp, char **g_env)
{
	char *str;
	char *content;

	if (tmp->next->type == 'q')
		tmp->next->content = quote_(tmp->next->content);
	content = NULL;
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			free_list(tmp);
			exit(1);
		}
		if (!ft_strncmp(str, tmp->next->content, ft_strlen(str)))
		{
			free(str);
			break ;
		}
		str = ft_strjoin(str, ft_strdup("\n"));
		content = ft_strjoin(content, str);
	}
	free(tmp->next->content);
	tmp->next->content = herdoc_appand(content, tmp->next->type, g_env);
}
