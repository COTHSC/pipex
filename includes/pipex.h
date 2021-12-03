/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:25:36 by jescully          #+#    #+#             */
/*   Updated: 2021/12/03 14:34:55 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>                                                          
# include <fcntl.h>   
# include "../libft/libft.h" 

typedef struct s_info {
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
	char	***cmds;
	char	**env;
	int		fd[2];
	int		fd_status;
}	t_info;

void	fill_struct(t_info *i, char **argv, char **env, int argc);
void	check_fd(int fd, char *filename, t_info *i);
void	check_pipe(t_info *i);
char	*try_paths(char **paths, char *command);
void	free_todo(t_info *info);
void	check_fd(int fd, char *filename, t_info *i);
char	*get_pwd(char **env, char *s);
char	*get_path(t_info *info, int i);
void	make_redirects(t_info *info, int i, int n);
int		close_unused_fds(int (*fd)[2], int current, int nb_cmds);
int		make_pipes(int (*fd)[2], int size);
#endif
