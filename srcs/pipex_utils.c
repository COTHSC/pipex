/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:26:29 by jescully          #+#    #+#             */
/*   Updated: 2021/09/30 19:26:33 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"                                                  

void	check_pipe(t_info *i)
{
	if (pipe(i->fd) == -1)
	{
		free(i);
		perror("Error: pipe failed");
		exit(1);
	}
}

void	fill_struct(t_info *i, char **argv, char **env)
{
	i->fd1 = open(argv[1], O_RDONLY);
	i->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	i->env = env;
	i->cmd1 = argv[2];
	i->cmd2 = argv[3];
	check_fd(i->fd2, argv[4], i);
	check_fd(i->fd1, argv[1], i);
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

void	check_fd(int fd, char *filename, t_info *i)
{
	char	*pwd;
	char	*temp;

	temp = get_pwd(i->env);
	pwd = ft_strjoin(temp, filename);
	free(temp);
	if (fd < 0)
	{
		if (access(pwd, F_OK) == 0)
		{
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else
		{
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		free(i);
		free(pwd);
		exit(1);
	}
	free(pwd);
}

char	*get_pwd(char **env)
{
	int	d;

	d = -1;
	while (env[++d])
		if (strncmp(env[d], "PWD", 3) == 0)
			return (ft_strjoin((env[d] + 4), "/"));
	return (NULL);
}
