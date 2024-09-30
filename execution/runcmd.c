#include "../minishell.h"

int	redirection(t_redir *cmd, char **env, int i)
{
	int	fd;
	int	std_copy;
	int	status;

	fd = open(cmd->file, cmd->mode, 0644);
	if (fd == -1)
	{
		perror(cmd->file);
		exit_s(1);
		return (0);
	}
	std_copy = dup(cmd->fd);
	dup2(fd, cmd->fd);
	status = runcmd(cmd->next, env , i);
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
		while (env[i][j] && name[k] && (env[i][j] == name[k]))
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
			ft_putstr_fd("Quit (core dumped)\n", 2);
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	return (1);
}

void	sig_handel(int sig)
{
	if (sig == SIGINT)
		printf("\n");
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
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
		if ((cmd->av[0][0] == '.' && cmd->av[0][1] == '/') || cmd->av[0][0] == '/')
		{
				if (access(cmd->av[0], F_OK) == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->av[0], 2);
					ft_putstr_fd(": No such file or directory\n", 2);
					// ft_putstr_fd("here\n", 2);
					exit(127);
				}
				if (check_dir(cmd->av[0]) == 0)
					exit(126);
				if (access(cmd->av[0], X_OK) == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->av[0], 2);
					ft_putstr_fd(": Permission denied\n", 2);
					exit(126);
				}
				if (execve(cmd->av[0], cmd->av, env) == -1)
				{
					perror("execve");
					free_g();
					exit(1);
				}
				check = 1;
		}
		if (cmd->av[0][0] == '.' && !cmd->av[0][1] &&!cmd->av[1])
		{
			ft_putstr_fd("minishell: .: filename argument required\n.: usage: . filename [arguments]\n", 2);
			free_g();
			exit(2);
		}
		cmd_path = ft_get_env("PATH", env);
		if (cmd_path == NULL)
		{
			if (access(cmd->av[0], F_OK) == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->av[0], 2);
					ft_putstr_fd(": No such file or directory\n", 2);
					// ft_putstr_fd("here\n", 2);
					exit(127);
				}
				if (check_dir(cmd->av[0]) == 0)
					exit(126);
				if (access(cmd->av[0], X_OK) == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->av[0], 2);
					ft_putstr_fd(": Permission denied\n", 2);
					exit(126);
				}
				if (execve(cmd->av[0], cmd->av, env) == -1)
				{
					perror("execve");
					free_g();
					exit(1);
				}
			printf("here\n");
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->av[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free_g();
			exit(127);
		}
		path = ft_ft_split(cmd_path, ':');
		while (path[i])
		{
			path[i] = ft_ft_strjoin(path[i], "/");
			path[i] = ft_ft_strjoin(path[i], cmd->av[0]);
			if (access(path[i], F_OK) == 0)
			{
				if ((cmd->av[0][0] == '.' && cmd->av[0][1] == '.' && !cmd->av[1]) || !cmd->av[0][0])
					break;
				if (execve(path[i], cmd->av, env) == -1)
				{
					perror("execve");
					free_g();
					exit(126);
				}
				check = 1;
			}
			i++;
		}
		if (cmd->av[0][0] == '"' || cmd->av[0][0] == '\'')
		{
			ft_putstr_fd("minishell: '':: command not found\n", 2);
			free_g();
			exit(127);
			check = 1;
		}
		if (cmd->av[0][0] == '\0')
		{
			free_g();
			exit(127);
			check = 1;
		}
		if (check == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->av[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free_g();
			exit(127);
		}
		free_g();
		exit(0);
	}
	else
	{
		signal(SIGINT, sig_handel);
		waitpid(pid, &status, 0);
		exit_s(check_exit_status(status));
	}
	return (ret_status());
}

int	heredoc(t_heredoc *cmd, char **env, int i)
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
		close(stdin_copy);
		free_g();
		exit(0);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	status = runcmd(cmd->next, env, i);
	dup2(stdin_copy, 0);
	close(stdin_copy);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	return (status);
}
int	ft_pipe(t_pipe *cmd, char **env, int i)
{
	int	fd[2];
	int	status;
	int	pid;
	int pid2;
	int	stdin_copy;

	// g_data.pipe__count++;
	pipe(fd);
	pid = fork();
	stdin_copy = dup(0);
	status = 0;
	signal(SIGINT, sig_handel);
	if (pid == 0)
	{
		signal(SIGINT, heandl_signal_child);
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		close(stdin_copy);
		i++;
		status = runcmd(cmd->left, env, i);
		free_g();
		// g_data.pipe__count--;
		exit(status);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			signal(SIGINT, heandl_signal_child);
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			close(stdin_copy);
			i++;
			status = runcmd(cmd->right, env, i);
			free_g();
			// g_data.pipe__count--;
			exit(status);
		}
	}
	if (i == 0)
		signal(SIGINT, sig_handel);
	// signal(SIGINT, handle_signal);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	dup2(stdin_copy, 0);
	close(stdin_copy);
	return (status);
}

int	runcmd(t_cmd *cmd, char **env, int i)
{
	if (cmd->type == PIPE)
	{
		return (ft_pipe((t_pipe *)cmd, env, i));
	}
	else if (cmd->type == HEREDOC)
	{
		return (heredoc((t_heredoc *)cmd, env, i));
	}
	if (cmd->type == REDIRECTION)
		return (redirection((t_redir *)cmd, env, i));
	if (cmd->type == EXEC)
		return (execute((t_exec *)cmd, env));
	return (1);
}
