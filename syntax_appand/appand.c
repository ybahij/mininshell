/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:24 by youssef           #+#    #+#             */
/*   Updated: 2024/10/01 13:42:38 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand(lexer_t *cmd)
{
	lexer_t	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->content && cm_strchr(tmp->content, '$'))
		{
			if (tmp->prev && tmp->prev->type == 'h' && tmp->type == 'q')
			{
				tmp = tmp->next;
				continue ;
			}
			expand_w(tmp);
			if (!tmp->content[0] && tmp->prev && cm_strchr("<>+",
					tmp->prev->type))
			{
				printf(RED "minishell: %s: ambiguous redirect\n" RESET,
					tmp->b_appand);
				return (exit_s(1), 1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	expand_w(lexer_t *cmd)
{
	int		fd[2];
	int		len;
	char	hold;

	len = 0;
	hold = 0;
	pipe(fd);
	cmd->b_appand = ft_ft_strdup(cmd->content);
	if (cmd->b_appand == NULL)
	{
		close(fd[0]);
		return (close(fd[1]), 1);
	}
	len = appand_in_fille(cmd, fd[1], hold);
	close(fd[1]);
	cmd->content = ft_malloc(len + 2);
	if (cmd->content == NULL)
		return (close(fd[0]), 1);
	read(fd[0], cmd->content, len);
	cmd->content[len] = '\0';
	close(fd[0]);
	return (0);
}

int	write_fd(int fd, char *str)
{
	int	len;

	len = 0;
	if (str)
		len = write(fd, str, ft_strlen(str));
	return (len);
}

int	appand_u(int *j, int i, lexer_t *cmd, int fd)
{
	char	*tmp2;
	int		len;
	int		k;

	len = 0;
	k = i;
	if (cmd->content[k] == '$')
	{
		len += write(fd, "$$", 2);
		*j = k + 1;
		return (len);
	}
	if (cmd->content[k] == '?')
	{
		*j = k + 1;
		return (write_fd(fd, ft_itoa(ret_status())));
	}
	while (cmd->content[k] && (ft_isalnum(cmd->content[k]) && !cm_strchr("\"'$",
				cmd->content[k])))
		k++;
	tmp2 = cheak_env(ft_ft_substr(cmd->content, i, k - i), *get_env());
	if (tmp2)
		len += write(fd, tmp2, ft_strlen(tmp2));
	*j = k;
	return (len);
}

int	appand_in_fille(lexer_t *cmd, int fd, char hold)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = 0;
	hold = 0;
	while (cmd->content[i])
	{
		if ((cmd->content[i] == '"' || cmd->content[i] == '\'') && hold == 0)
			hold = cmd->content[i];
		else if (cmd->content[i] == hold)
			hold = 0;
		if (hold != '\'' && cmd->content[i] == '$' && (ft_isalnum(cmd->content[i
						+ 1]) || ft_strchr("\"'$?", cmd->content[i + 1])))
		{
			i++;
			len += appand_u(&j, i, cmd, fd);
			i = j;
		}
		else
			len += write(fd, &cmd->content[i++], 1);
	}
	return (len);
}
