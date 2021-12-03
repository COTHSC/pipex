/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:09:33 by jescully          #+#    #+#             */
/*   Updated: 2021/12/03 14:37:43 by jescully         ###   ########.fr       */
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

void	free_todo(t_info *info)
{
	int	i;
	int	d;

	i = 0;
	while (info->cmds[i])
	{
		d = 0;
		while (info->cmds[i][d])
			free(info->cmds[i][d++]);
		free(info->cmds[i++]);
	}
	free(info->cmds);
}

void	fill_struct(t_info *i, char **argv, char **env, int argc)
{
	int	n;
	int	index;

	n = 2;
	index = 0;
	i->env = env;
	i->fd1 = open(argv[1], O_RDONLY);
	i->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	check_fd(i->fd2, argv[argc - 1], i);
	check_fd(i->fd1, argv[1], i);
	i->cmds = ft_calloc(sizeof(char *), argc - 2);
	if (!i->cmds)
		exit (1);
	while (n < argc - 1)
	{
		i->cmds[index] = ft_split(argv[n], ' ');
		n++;
		index++;
	}
}

void	check_fd(int fd, char *filename, t_info *i)
{
	char	*pwd;
	char	*temp;

	temp = get_pwd(i->env, "PWD");
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
		free(pwd);
		exit(errno);
	}
	free(pwd);
}

char	*get_pwd(char **env, char *s)
{
	int	d;

	d = -1;
	while (env[++d])
	{
		if (ft_strncmp(env[d], s, ft_strlen(s)) == 0)
		{
			if (ft_strncmp(env[d], "PWD", 3) == 0)
				return (ft_strjoin((env[d] + 4), "/"));
			else
				return (env[d] + 5);
		}
	}
	return (NULL);
}
