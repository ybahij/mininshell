
#include "minishell.h"

int	token_cmd(char *line, lexer_t **cmd, char **env)
{
	*cmd = ferst_s(line);
	if (!(*cmd))
		return (free_garbage(), 1);
	if (cmd_syntax(*cmd, env))
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
			break ;
		add_garbage(line);
		if (*line)
			add_history(line);
		if (token_cmd(line, &cmd, env))
			continue ;
		print_tree(parse_and(cmd, env));
		free_garbage();
	}
	return (0);
}
