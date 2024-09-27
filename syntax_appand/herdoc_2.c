/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:20:40 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/27 19:44:11 by ybahij           ###   ########.fr       */
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
	tmp2 = cheak_env(ft_ft_substr(content, k, j - k), g_env);
	if (tmp2)
		str = ft__strjoin(str, tmp2);
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
		ft_putstr_fd("minishell: maximum number of here-document exceeded\n", 2);
		exit(2);
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
			str = ft__strjoin(str, ft_ft_substr(content, i, 1));
			i++;
		}
	}
	return (str);
}

void	exit_heredoc(int fd, char *str, char *delim)
{
	(void)str;
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
	free_g();
	close(fd);
	exit(1);
}
void	read_herdoc(int fd, char *delim)
{
	char	*str;

	str = NULL;
	set_fd(fd,0);
	signal(SIGINT, handle_heredoc_signal);
	while (1)
	{
		str = readline(">");
		if (!str)
			exit_heredoc(fd, str, delim);
		add_garbage(str);
		if (!ft_strncmp(str, delim, ft_strlen(str)))
		{
			write(fd, "\0", 1);
			break;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	free_g();
	close(fd);
	exit(0);
}
