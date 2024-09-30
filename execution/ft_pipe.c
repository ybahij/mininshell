// int	ft_pipe(t_pipe *cmd, char **env, int i)
// {
// 	int	fd[2];
// 	int	status;
// 	int	pid;
// 	int pid2;
// 	int	stdin_copy;

// 	// g_data.pipe__count++;
// 	pipe(fd);
// 	pid = fork();
// 	stdin_copy = dup(0);
// 	status = 0;
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, heandl_signal_child);
// 		close(fd[0]);
// 		dup2(fd[1], 1);
// 		close(fd[1]);
// 		close(stdin_copy);
// 		i++;
// 		status = runcmd(cmd->left, env, i);
// 		free_g();
// 		// g_data.pipe__count--;
// 		exit(status);
// 	}
// 	else
// 	{
// 		pid2 = fork();
// 		if (pid2 == 0)
// 		{
// 			signal(SIGINT, heandl_signal_child);
// 			close(fd[1]);
// 			dup2(fd[0], 0);
// 			close(fd[0]);
// 			close(stdin_copy);
// 			i++;
// 			status = runcmd(cmd->right, env, i);
// 			free_g();
// 			// g_data.pipe__count--;
// 			exit(status);
// 		}
// 	}
// 	if (i == 0)
// 		signal(SIGINT, sig_handel);
// 	// signal(SIGINT, handle_signal);
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	dup2(stdin_copy, 0);
// 	close(stdin_copy);
// 	return (status);
// }