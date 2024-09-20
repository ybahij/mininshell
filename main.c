/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:37:50 by youssef           #+#    #+#             */
/*   Updated: 2024/09/20 15:55:54 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int g_data;

int	paranthesis__(lexer_t *cmd)
{
	lexer_t	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == '(' && tmp->next && cm_strchr("qw", tmp->next->type))
		{
			exit_s(2);
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

int	dblptr_len(char **dblptr)
{
	int	i;

	i = 0;
	while (dblptr[i])
		i++;
	return (i);
}
char	**new_envi(void)
{
	char	**new_env;

	char	*PATH = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	new_env = malloc(sizeof(char *) * 2);
	new_env[0] = cm_strdup(PATH);
	new_env[1] = NULL;
	return (new_env);
}

char	**get_copy_with_malloc(char **env)
{
	int	i;
	char	**new_env;
	if (env[0] == NULL)
		return (new_envi());
	new_env = malloc(sizeof(char *) * (dblptr_len(env) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = cm_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char    ***get_env(void)
{
	static char **env;

	return (&env);
}

void	cm_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	lexer_t	*cmd;

	(void)ac;
	(void)av;
	*get_env() = get_copy_with_malloc(env);
	line = NULL;
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		printf("status >> %d\n", ret_status());
		line = readline("minishell$ ");
		if (!line)
		{
			cm_free(*get_env());
			clear_history();
			printf("exit\n");
			free_garbage();
			exit(0);
		}
 		add_garbage(line);
		if (*line)
			add_history(line);
		if (token_cmd(line, &cmd, *get_env(), "newline"))
			continue ;
		// print_tree(parse_and(cmd, *get_env()));
		runcmd(parse_and(cmd, *get_env()), *get_env());
		free_garbage();
	}
	return (0);
}
