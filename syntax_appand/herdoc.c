/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:50:59 by youssef           #+#    #+#             */
/*   Updated: 2024/09/22 23:19:00 by ybahij           ###   ########.fr       */
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
	// fd = open(fname, O_RDWR);
	// if (fd == -1)
	// 	return(printf("minishell: open failed\n"), NULL);
	content = NULL;
	while (1)
	{
		
		r = read(fd, str, 1);
		printf("r = %d\n", r);
		if (r <= 0)
		{
			str[r] = '\0';
			break;
		}
		printf("test\n");
		str[r] = '\0';
		tmp = ft_strdup(str);
		if (!tmp)
			return (close(fd), NULL);
		content = ft_strjoin(content, tmp);
		if (!content)
			return (close(fd), NULL);
	}
	close(fd);
	return (content);
}

int	herdoc_ut(int fd, char *fname, lexer_t *tmp, char **env)
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
		unlink(fname);
		return (0);
	}
	content = read_file(fd);
	if (!content)
		return (0);
	tmp->next->content = herdoc_appand(content, tmp->next->type, env);
	close(fd);
	// unlink(fname);
	return (1);
}

int handle_heredoc(lexer_t *tmp, char **env)
{
	char fname[11];
	int pid;
	int fd[2];
	// int r;
	
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
	if (!herdoc_ut(fd[0], fname, tmp, env))
		return (0);
	return (1);
}

// int	handle_heredoc(lexer_t *tmp, char **env)
// {
// 	char fname[11];
// 	int pid;
// 	int fd;
// 	int	r;

// 	if (tmp->next->type == 'q')
// 		tmp->next->content = quote_(tmp->next->content);
// 	fd = open("/dev/random", O_RDWR);
// 	r = read(fd, fname, 10);
// 	fname[r] = '\0';
// 	close(fd);
// 	fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	signal(SIGINT, SIG_IGN);
// 	pid = fork();
// 	if (pid == 0)
// 		read_herdoc(fd, tmp->next->content);
// 	if (!herdoc_ut(fd, fname, tmp, env))
// 		return (0);
// 	return (1);
// }


