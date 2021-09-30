/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:25:36 by jescully          #+#    #+#             */
/*   Updated: 2021/09/30 19:25:40 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>                                                            
# include <unistd.h>                                                            
# include <string.h>                                                            
# include <stdio.h>                                                             
# include <sys/wait.h>                                                          
# include <fcntl.h>   
# include "../libft/libft.h" 

typedef struct s_info {
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
	char	**env;
	int		fd[2];
	int		fd_status;
}	t_info;

void	fill_struct(t_info *i, char **argv, char **env);
void	check_fd(int fd, char *filename, t_info *i);
void	check_pipe(t_info *i);
char	*try_paths(char **paths, char *command);
void	check_fd(int fd, char *filename, t_info *i);
char	*get_pwd(char **env);

#endif
