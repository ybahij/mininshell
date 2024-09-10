/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:37:50 by youssef           #+#    #+#             */
/*   Updated: 2024/09/10 21:43:16 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	paranthesis__(lexer_t *cmd)
{
	lexer_t	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == '(' && tmp->next && cm_strchr("qw", tmp->next->type))
		{
			printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
				tmp->next->content);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	paranthesis_syntax(lexer_t *cmd, char **env)
{
	lexer_t	*tmp;
	lexer_t	*tmp2;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == '(')
		{
			if (token_cmd(remaove_parenthesis(tmp->content), &tmp2, env, "("))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	cheak_dollar_p(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '=')
	{
		if (input[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

void	cheak_for_equal(lexer_t *cmd)
{
	lexer_t	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == 'w' && cm_strchr(tmp->content, '=')
			&& cm_strchr(tmp->content, '$'))
		{
			if (cheak_dollar_p(tmp->content))
			{
				tmp->content = ft_strjoin("\"", tmp->content);
				tmp->content = ft_strjoin(tmp->content, "\"");
			}
		}
		tmp = tmp->next;
	}
}

int	token_cmd(char *line, lexer_t **cmd, char **env, char *newline)
{
	lexer_t	*tmp;

	tmp = NULL;
	*cmd = ferst_s(line);
	if (!(*cmd))
		return (free_garbage(), 1);
	if (paranthesis__(*cmd))
		return (free_garbage(), 1);
	if (cmd_syntax(*cmd, env, newline, tmp))
		return (free_garbage(), 1);
	if (paranthesis_syntax(*cmd, env))
		return (free_garbage(), 1);
	cheak_for_equal(*cmd);
	if (expand(*cmd, env))
		return (free_garbage(), 1);
	if (!(*cmd))
		return (free_garbage(), 1);
	if (!split_cmd(*cmd))
		return (free_garbage(), 1);
	del_quote(*cmd);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	lexer_t	*cmd;

	(void)ac;
	(void)av;
	line = NULL;
	while (1)
	{
		signal(SIGINT, handle_signal);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			free_garbage();
			exit(0);
		}
		add_garbage(line);
		if (*line)
			add_history(line);
		if (token_cmd(line, &cmd, env, "newline"))
			continue ;
		print_tree(parse_and(cmd, env));
		free_garbage();
	}
	return (0);
}
