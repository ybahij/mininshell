/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:26:24 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/29 13:26:55 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (tmp);
}
