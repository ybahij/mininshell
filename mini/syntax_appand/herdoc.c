/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:50:59 by youssef           #+#    #+#             */
/*   Updated: 2024/09/06 23:03:12 by youssef          ###   ########.fr       */
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

	i = 0;
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
		exit(1);
	}
}

char	*herdoc_appand(char *content, char type, char **g_env)
{
	char	*str;
	int		i;

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
	return (str);
}

int	herdoc_pipe(int	fd, char *end)
{
	char	*str;

	signal(SIGINT, handel_herdoc_segnal);
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			//free(str);
			return (0);
		}
		if (!ft_strncmp(str, end, ft_strlen(str)))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	exit (1);
}

int	heandal_herdoc(lexer_t *tmp, char **g_env)
{
	char	*str;
	char	*content;
	int		fd[2];

	if (tmp->next->type == 'q')
		tmp->next->content = quote_(tmp->next->content);
	content = NULL;
	pipe(fd);
	dup2(0, fd[0]);
	while (1)
	{
		signal(SIGINT, handel_herdoc_segnal);
		str = readline(">");
		if (!str)
		{
			free(str);
			dup2(fd[0], 0);
			return (0);
		}
		add_garbage(str);
		if (!ft_strncmp(str, tmp->next->content, ft_strlen(str)))
			break ;
		str = ft_strjoin(str, ft_strdup("\n"));
		content = ft_strjoin(content, str);
	}

	tmp->next->content = herdoc_appand(content, tmp->next->type, g_env);
	return (1);
}
