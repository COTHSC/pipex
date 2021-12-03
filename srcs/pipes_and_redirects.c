/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:12:54 by jescully          #+#    #+#             */
/*   Updated: 2021/12/03 14:41:01 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(t_info *info, int i)
{
	char	**paths;
	int		d;
	char	*path;

	d = 0;
	paths = ft_split(get_pwd(info->env, "PATH"), ':');
	path = try_paths(paths, info->cmds[i][0]);
	if (!path)
	{
		if (access(info->cmds[i][0], F_OK) == 0)
			return (info->cmds[i][0]);
		d = 0;
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(info->cmds[i][0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_todo(info);
		exit(127);
	}
	return (path);
}

char	*try_paths(char **paths, char *command)
{
	int		d;
	char	*path_bits;
	char	*path;

	d = -1;
	while (paths[++d])
	{
		path_bits = ft_strjoin(paths[d], "/");
		path = ft_strjoin(path_bits, command);
		free(path_bits);
		if (access(path, F_OK) == 0)
		{
			d = 0;
			while (paths[d])
				free(paths[d++]);
			free(paths);
			return (path);
		}
		free(path);
	}
	d = 0;
	while (paths[d])
		free(paths[d++]);
	free(paths);
	return (NULL);
}

void	make_redirects(t_info *info, int i, int n)
{
	if (i == n - 1)
		dup2(info->fd2, STDOUT_FILENO);
	if (i == 0)
		dup2(info->fd1, STDIN_FILENO);
}

int	close_unused_fds(int (*fd)[2], int current, int nb_cmds)
{
	int	idx;
	int	current_read;
	int	current_write;
	int	ret;

	idx = 0;
	ret = 0;
	current_read = current;
	current_write = current + 1;
	while (idx < nb_cmds)
	{
		if (idx != current_read)
			ret = close(fd[idx][0]);
		if (idx != current_write)
			ret = close(fd[idx][1]);
		if (ret < 0)
			return (0);
		idx++;
	}
	return (1);
}

int	make_pipes(int (*fd)[2], int size)
{
	int	i;

	i = 0;
	while (i < size + 1)
	{
		if (pipe(fd[i]) < 0)
			exit (1);
		i++;
	}
	return (0);
}
