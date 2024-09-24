/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:50:59 by youssef           #+#    #+#             */
/*   Updated: 2024/09/24 18:02:21 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global g_data;

char *read_file(int fd)
{
	char *content;
	char *str;
	char *tmp;
	int r;

	str = ft_malloc(2);
	if (!str)
		return (NULL);
	content = NULL;
	while (1) 
	{
		r = read(fd, str, 1);
		if (r <= 0)
			break;
		str[r] = '\0';
		tmp = ft_ft_strdup(str);
		content = ft__strjoin(content, tmp);
	}
	close(fd);
	return (content);
}

int	herdoc_ut(int fd, lexer_t *tmp, char **env)
{
	int ex_status;
	int status;
	char *content;

	waitpid(-1, &status, 0);
	ex_status = (status >> 8) & 0xFF;
	if (ex_status == 1 || ex_status == 2)
	{
		if (ex_status == 2)
			exit_s(130);
		else
			exit_s(0);
		close(fd);
		return (0);
	}
	content = read_file(fd);
	if (!content)
		return (0);
	tmp->next->content = herdoc_appand(content, tmp->next->type, env);
	close(fd);
	return (1);
}

int handle_heredoc(lexer_t *tmp, char **env)
{
	int pid;
	int fd[2];
	
	if (tmp->next->type == 'q')
		tmp->next->content = quote_(tmp->next->content);
	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0) 
	{
    	close(fd[0]);
    	read_herdoc(fd[1], tmp->next->content);
	} 
	else 
	{
		close(fd[1]);
		if (!herdoc_ut(fd[0], tmp, env))
			return (0);
	}
	return (1);
}



