/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:10:09 by jescully          #+#    #+#             */
/*   Updated: 2021/12/03 14:51:38 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	execute_binary(t_info *info, int i)
{
	char	*path;

	path = get_path(info, i);
	if (!path)
		exit(1);
	if ((execve(path, info->cmds[i], info->env)) == -1)
	{
		free(path);
		free_todo(info);
		exit(EXIT_FAILURE);
	}
	free (path);
	return (0);
}

int	execute_child(t_info *info, int (*fd)[2], int i, int n)
{
	if (!close_unused_fds(fd, i, n))
		exit(EXIT_FAILURE);
	dup2(fd[i][0], STDIN_FILENO);
	if (i != n - 1)
		dup2(fd[i + 1][1], STDOUT_FILENO);
	make_redirects(info, i, n);
	if (execute_binary(info, i))
		return (1);
	char *d = malloc(2);
	(void)d;
	close(fd[i][0]);
	close(fd[i + 1][1]);
	return (0);
}

static int	wait_and_set_ret(int pids[FD_SETSIZE / 2], int n)
{
	int			ret;
	int			status;
	int			ended_pid;

	ended_pid = 1;
	ret = 0;
	while (ended_pid > 0)
	{
		ended_pid = wait(&status);
		if (ended_pid == pids[n])
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ret = WTERMSIG(status);
			else
				ret = 1;
		}
	}
	(void)pids;
	return (ret);
}

int	ft_multipipes2(t_info *info)
{
	int	fd[FD_SETSIZE][2];
	int	i;
	int	pids[FD_SETSIZE / 2];
	int	status;
	int	n;

	n = 0;
	while (info->cmds[n])
		n++;
	make_pipes(fd, n);
	i = 0;
	status = 0;
	while (i < n && info->cmds[i])
	{
		pids[i] = fork();
		if (pids[i] == 0)
			execute_child(info, fd, i, n);
		i++;
	}
	close_unused_fds(fd, n + 1, n);
	status = wait_and_set_ret(pids, n - 1);
	close(fd[n][1]);
	close(fd[n][0]);
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	t_info	i;
	int		status;

	status = 0;
	if (argc >= 5)
	{
		fill_struct(&i, argv, env, argc);
		status = ft_multipipes2(&i);
		free_todo(&i);
		return (status);
	}
	return (1);
}
