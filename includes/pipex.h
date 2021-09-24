#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>                                                            
#include <unistd.h>                                                            
#include <string.h>                                                            
#include <stdio.h>                                                             
#include <sys/wait.h>                                                          
#include <fcntl.h>   
#include "../libft/libft.h" 


typedef struct s_info {
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
	char	**env;
	int		fd[2];
	int		fd_status;
}	t_info;


#endif

