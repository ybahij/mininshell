/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:50:59 by youssef           #+#    #+#             */
/*   Updated: 2024/09/10 03:00:13 by youssef          ###   ########.fr       */
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

void	read_herdoc(int fd, char *delim)
{
	char	*str;

	str = NULL;
	signal(SIGINT, handle_heredoc_signal);
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			free(str);
			close(fd);
			printf(RED"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n"RESET, delim);
			exit(0);
		}
		if (!ft_strncmp(str, delim, ft_strlen(str)))
			break;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
	exit(0);
}

char *read_file(char *fname)
{
	int fd;
	char *content;
	char str[2];
	char *tmp;
	int r;

	fd = open(fname, O_RDWR);
	content = NULL;
	while (1)
	{
		r = read(fd, str, 1);
		if (r == 0)
			break;
		str[r] = '\0';
		tmp = ft_strdup(str);
		content = ft_strjoin(content, tmp);
	}
	close(fd);
	return (content);
}

int	handle_heredoc(lexer_t *tmp, char **env)
{
	char fname[11];
	char *content;
	int	status;
	int pid;
	int fd;
	int	r;
	int ex_status;

	if (tmp->next->type == 'q')
		tmp->next->content = quote_(tmp->next->content);
	fd = open("/dev/random", O_RDWR);
	r = read(fd, fname, 10);
	fname[r] = '\0';
	close(fd);
	fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		read_herdoc(fd, tmp->next->content);
	waitpid(-1, &status, 0);
	ex_status = (status >> 8) & 0xFF;
	if (ex_status == 1)
	{
		close(fd);
		unlink(fname);
		return (0);
	}
	content = read_file(fname);
	tmp->next->content = herdoc_appand(content, tmp->next->type, env);
	close(fd);
	unlink(fname);
	return (1);
}


