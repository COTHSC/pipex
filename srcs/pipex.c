/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:26:02 by jescully          #+#    #+#             */
/*   Updated: 2021/09/30 19:26:07 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(t_info *i, char **command, char *argv)
{
	char	**paths;
	int		d;
	char	*path;

	if (access(command[0], F_OK) == 0)
		return (command[0]);
	d = 0;
	while (ft_strnstr(i->env[d], "PATH", 4) == 0)
		d++;
	paths = ft_split(i->env[d] + 5, ':');
	path = try_paths(paths, command[0]);
	if (!path)
	{
		d = 0;
		while (command[d])
			free(command[d++]);
		free(command);
		free(i);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(0);
	}
	return (path);
}

void	execute(t_info *i, char *argv)
{
	char	**command;
	int		d;
	char	*path;

	command = ft_split(argv, ' ');
	d = 0;
	path = get_path(i, command, argv);
	if (execve(path, command, i->env) == -1)
	{
		free(path);
		while (command[d])
			free(command[d++]);
		free(command);
		free(i);
		exit(0);
	}
	free (path);
}

void	execute_child(t_info *i)
{
	close(i->fd[0]);
	dup2(i->fd1, 0);
	dup2(i->fd[1], 1);
	close(i->fd[1]);
	execute(i, i->cmd1);
}

void	execute_parent(t_info *i)
{
	close(i->fd[1]);
	dup2(i->fd[0], 0);
	dup2(i->fd2, 1);
	close(i->fd[0]);
	execute(i, i->cmd2);
}

int	main(int argc, char **argv, char **env)
{
	t_info	*i;
	int		pid1;
	int		status;

	status = 0;
	if (argc == 5)
	{
		i = (t_info *)malloc(sizeof(t_info));
		check_pipe(i);
		fill_struct(i, argv, env);
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("Error: Failed to fork child process");
			exit(1);
		}
		else if (pid1 == 0)
			execute_child(i);
		execute_parent(i);
		free(i);
		return (0);
	}
	return (1);
}
