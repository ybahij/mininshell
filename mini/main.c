/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:37:50 by youssef           #+#    #+#             */
/*   Updated: 2024/09/03 15:27:03 by youssef          ###   ########.fr       */
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
	int		i;

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

int	token_cmd(char *line, lexer_t **cmd, char **env, char *newline)
{
	lexer_t	*tmp;

	*cmd = ferst_s(line);
	if (!(*cmd))
		return (free_garbage(), 1);
	if (paranthesis__(*cmd))
		return (free_garbage(), 1);
	if (cmd_syntax(*cmd, env, newline, tmp))
		return (free_garbage(), 1);
	if (paranthesis_syntax(*cmd, env))
		return (free_garbage(), 1);
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

	line = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			free(line);
			break ;
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
