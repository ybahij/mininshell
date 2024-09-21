#include "../minishell.h"

// extern t_struct	g_data;
// extern int	g_data;

int	redirection(t_redir *cmd, char **env)
{
	int	fd;
	int	std_copy;
	int	status;

	fd = open(cmd->file, cmd->mode, 0644);
	if (fd == -1)
	{
		perror(cmd->file);
		return (0);
	}
	std_copy = dup(cmd->fd);
	dup2(fd, cmd->fd);
	status = runcmd(cmd->next, env);
	dup2(std_copy, cmd->fd);
	close(std_copy);
	return (status);
}

char	*ft_get_env(char *name, char **env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] && env[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (env[i][j] == '=' && name[k] == '\0')
			return (env[i] + j + 1);
		i++;
	}
	return (NULL);
}

int	check_exit_status(int status)
{
	int	signal_number;

	if (((status)&0x7f) != 0 && ((status)&0x7f) != 0x7f)
	{
		signal_number = (status)&0x7f;
		if (signal_number == SIGQUIT)
		{
			printf("Quit (core dumped)\n");
			return (((status) & 0x7f) + 128);
		}
		else if (signal_number == SIGINT)
		{
			return (((status) & 0x7f) + 128);
		}
	}
	else if (((status)&0x7f) == 0)
	{
		return ((status >> 8) & 0xff); // Return the exit status
	}
	return (-1); // Return -1 for unknown status
}

int	check_dir(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == -1)
	{
		perror("stat");
		exit(1);
	}
	if (S_ISDIR(buf.st_mode))
	{
		printf("minishell: %s: is a directory\n", cmd);
		exit(126);
	}
	return (1);
}

int	execute(t_exec *cmd, char **env)
{
	int		pid;
	int		status;
	char	**path;
	int		i;
	char	*cmd_path;
	int		check;

	check = 0;
	if (cmd->av[0] == NULL)
		return (1);
	if (builtins(cmd, env) == 1)
		return (1);
	pid = fork();
	i = 0;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
		if ((cmd->av[0][0] == '.' && cmd->av[0][1] == '/') || cmd->av[0][0] == '/')
		{
			printf("test\n");
				if (access(cmd->av[0], F_OK) == -1)
				{
					printf("minishell: %s: No such file or directory\n", cmd->av[0]);
					exit(127);
				}
				if (check_dir(cmd->av[0]) == 0)
					exit(126);
				if (access(cmd->av[0], X_OK) == -1)
				{
					printf("minishell: %s: Permission denied\n", cmd->av[0]);
					exit(126);
				}
				// check_dir(cmd->av[0]);
				if (execve(cmd->av[0], cmd->av, env) == -1)
				{
					cm_free(env);
					// free(cmd);
					perror("execve");
					free_g();
					exit(1);
				}
				check = 1;
		}
		cmd_path = ft_get_env("PATH", env);
		if (cmd_path == NULL)
		{
			printf("minishell: %s: command not found\n", cmd->av[0]);
			exit(127);
		}
		path = ft_ft_split(cmd_path, ':');
		while (path[i])
		{
			path[i] = ft_ft_strjoin(path[i], "/");
			path[i] = ft_ft_strjoin(path[i], cmd->av[0]);
			if (access(path[i], F_OK) == 0)
			{
				if (execve(path[i], cmd->av, env) == -1)
				{
					cm_free(env);
					perror("execve");
					exit(126);
				}
				check = 1;
			}
			i++;
		}
		if (check == 0)
		{
			printf("minishell: %s: command not found\n", cmd->av[0]);
			exit(127);
		}
		cm_free(env);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		exit_s(check_exit_status(status));
	}
	return (1);
}

int	heredoc(t_heredoc *cmd, char **env)
{
	int	fd[2];
	int	pid;
	int	stdin_copy;
	int	status;

	pipe(fd);
	pid = fork();
	stdin_copy = dup(0);
	if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], cmd->content, ft_strlen(cmd->content));
		close(fd[1]);
		free(cmd);
		// cm_free(env);
		exit(0);
		// must free ga3 lkhra
	}
	close(fd[1]);
	dup2(fd[0], 0);
	status = runcmd(cmd->next, env);
	dup2(stdin_copy, 0);
	waitpid(pid, NULL, 0);
	return (status);
}
int	ft_pipe(t_pipe *cmd, char **env)
{
	int	fd[2];
	int	status;
	int	pid;
	int	stdin_copy;

	pipe(fd);
	pid = fork();
	stdin_copy = dup(0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		status = runcmd(cmd->left, env);
		// cm_free(env);
		free(cmd);
		exit(status);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	status = runcmd(cmd->right, env);
	dup2(stdin_copy, 0);
	close(stdin_copy);
	waitpid(pid, NULL, 0);
	return (status);
}

int	runcmd(t_cmd *cmd, char **env)
{
	if (cmd->type == AND)
	{
		if (runcmd(((t_and *)cmd)->left, env))
			runcmd(((t_and *)cmd)->right, env);
	}
	else if (cmd->type == OR)
	{
		if (runcmd(((t_or *)cmd)->left, env) == 0)
			runcmd(((t_or *)cmd)->right, env);
	}
	else if (cmd->type == PIPE)
	{
		return (ft_pipe((t_pipe *)cmd, env));
	}
	else if (cmd->type == HEREDOC)
	{
		return (heredoc((t_heredoc *)cmd, env));
	}
	if (cmd->type == REDIRECTION)
		return (redirection((t_redir *)cmd, env));
	if (cmd->type == EXEC)
		return (execute((t_exec *)cmd, env));
	return (1);
}
