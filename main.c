/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:37:50 by youssef           #+#    #+#             */
/*   Updated: 2024/09/30 15:02:46 by ybahij           ###   ########.fr       */
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
			exit_s(2);
			printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
				tmp->next->content);
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

int	cheak_for_equal(lexer_t *cmd)
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
				if (!tmp->content)
					return (1);
				tmp->content = ft_strjoin(tmp->content, "\"");
				if (!tmp->content)
					return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	token_cmd(char *line, lexer_t **cmd, char **env, char *newline)
{
	lexer_t	*tmp;

	tmp = NULL;
	*cmd = ferst_s(line);
	if (!(*cmd))
		return (1);
	if (cmd_syntax(*cmd, env, newline, tmp))
		return (1);
	if (cheak_for_equal(*cmd))
		return (1);
	if (expand(*cmd))
		return (1);
	if (!(*cmd))
		return (1);
	if (!split_cmd(*cmd))
		return (1);
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
	char	*pwd;
	
	new_env = ft_malloc(sizeof(char *) * 4);
	if (!new_env)
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		exit(1);
	}
	new_env[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("_=/usr/bin/env");
	new_env[3] = NULL;
	if (!new_env[0])
		return (NULL);
	new_env[1] = NULL;
	return (new_env);
}

void	shell_lvl(char **env)
{
	int		i;
	int		lvl;
	char	*shlvl;
	char	*new_shlvl;

	i = 0;
	lvl = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_strdup(env[i] + 6);
			if (!shlvl)
				return ;
			lvl = ft_atoi(shlvl);
			break ;
		}
		i++;
	}
	if (lvl >= 1000)
	{	
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(ft_itoa(lvl + 1), 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		lvl = 1;
	}
	else if (lvl < 0)
		lvl = 0;
	else
		lvl++;
	new_shlvl = ft_itoa(lvl);
	if (!new_shlvl)
		return ;
	env[i] = ft_strjoin("SHLVL=", new_shlvl);
}

char	**get_copy_with_malloc(char **env)
{
	int	i;
	char	**new_env;
	if (env[0] == NULL)
		return (new_envi());
	new_env = ft_malloc(sizeof(char *) * (dblptr_len(env) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
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
	char	*holder;

	char 	*cwd;

	// g_data.pipe__count = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		exit(1);
	}
	free(cwd);
	(void)ac;
	(void)av;
	*get_env() = get_copy_with_malloc(env);
	shell_lvl(*get_env());
	line = NULL;
	holder = getcwd(NULL, 0);
	g_data.pwd = ft_strdup(holder);
	free(holder);
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		if (!line)
		{
			clear_history();
			printf("exit\n");
			free(line);
			free_g();
			exit(ret_status());
		}
 		add_garbage(line);
		if (*line)
			add_history(line);
		if (token_cmd(line, &cmd, *get_env(), "newline"))
		{
			// free(line);
			continue ;}
		// print_tree(parse_pipe(cmd, *get_env()));
		runcmd(parse_pipe(cmd, *get_env()), *get_env(), 0);
	}
	return (0);
}