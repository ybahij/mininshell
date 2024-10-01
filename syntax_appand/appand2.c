/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:26:24 by ybahij            #+#    #+#             */
/*   Updated: 2024/10/01 17:03:42 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dellt__(lexer_t *tmp)
{
	lexer_t	*tmp2;

	tmp2 = tmp;
	while (tmp2)
	{
		if (cm_strchr(tmp2->content, 1))
			tmp2->content = dellt_escap(tmp2->content);
		tmp2 = tmp2->next;
	}
}

char *dellt_escap(char *str)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = ft_malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == 1)
		{
			i++;
			continue;
		}
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	write_(int fd, char *tmp, int len)
{
	int i;
	char c;

	i = 0;
	c = 1;
	while(tmp[i])
	{
		if (tmp[i] == '"' || tmp[i] == '\'')
		{
			len += write(fd, &c, 1);
			len += write(fd, &tmp[i], 1);
		}
		else
			len += write(fd, &tmp[i], 1);
		i++;
	}
	return (len);
}

char *add_escape(char *tmp)
{
	char *tmp2;
	int	fd[2];
	int len;

	if (!tmp || (!ft_strchr(tmp, '\'') && !ft_strchr(tmp, '"')))
		return (tmp);
	len = 0;
	pipe(fd);
	len = write_(fd[1], tmp, len);
	close(fd[1]);
	tmp2 = ft_malloc(len + 1);
	read(fd[0], tmp2, len);
	tmp2[len] = '\0';
	close(fd[0]);
	return (tmp2);
}

char	*cheak_env(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)))
		{
			i++;
			continue ;
		}
		if (env[i][ft_strlen(str)] == '=')
		{
			tmp = ft_ft_strdup(&env[i][ft_strlen(str) + 1]);
		}
		if (tmp)
			break ;
		i++;
	}
	if (!ft_strcmp(str, "PWD") && !tmp)
		tmp = ft_ft_strdup(g_data.pwd);
	else if (!ft_strcmp(str, "OLDPWD") && !tmp)
		tmp = ft_ft_strdup(g_data.old_pwd);
	return (add_escape(tmp));
}
