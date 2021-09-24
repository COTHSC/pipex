#include "../includes/pipex.h"



char *get_path(t_info *i, char *command)
{
	char **paths;
	char *path;
	int d;
	char *path_bits;

	d = 0;
	while (ft_strnstr(i->env[d], "PATH", 4) == 0)
		d++;
	paths = ft_split(i->env[d] + 5, ':');
	d = 0;
	while (paths[d])
	{
		path_bits = ft_strjoin(paths[d], "/");
		path = ft_strjoin(path_bits, command);
		free(path_bits);
		if (access(path, F_OK) == 0)
			return path;
		d++;
	}
	exit(EXIT_FAILURE);
	return (0);
}

void execute(t_info *i, char *argv)
{
	char **command;

	command = ft_split(argv, ' ');
	if (execve(get_path(i, command[0]), command, i->env) == -1)
			exit(EXIT_FAILURE);
}

void execute_child(t_info *i)
{
	close(i->fd[0]);
	dup2(i->fd1, 0);
	dup2(i->fd[1], 1);
	close(i->fd[1]);
	execute(i, i->cmd1);
}

void execute_parent(t_info *i)
{

	close(i->fd[1]);
	dup2(i->fd[0], 0);
	dup2(i->fd2, 1);
	close(i->fd[0]);
	execute(i, i->cmd2);
}
int main(int argc, char **argv, char **env)
{
	t_info *i;
	int pid;

	if (argc == 5)
	{
		i = (t_info *)malloc(sizeof(t_info));
		if (pipe(i->fd) == -1)
			return -1;
		i->fd1 = open(argv[1], O_RDONLY);
		i->fd2 =  open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		i->env = env;
		i->cmd1 = argv[2];
		i->cmd2 = argv[3];

		pid = fork();

		if (pid == -1)
			printf("error during fork\n");
		else if (pid == 0)
		{
			execute_child(i);
			exit(1);
		}
		execute_parent(i);
//		close(i->fd[0]);
//		close(i->fd[1]);
	}
}

