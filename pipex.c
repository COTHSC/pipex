/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:59:23 by jescully          #+#    #+#             */
/*   Updated: 2021/09/08 11:52:18 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *cmd1;

    cmd1 = argv[1];
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe: ");
        exit(1);
    }
    int childPid = fork();
    if (childPid == 0) 
    {
        char *av[] = {
            argv[2],
            argv[1],
            NULL,
        };

        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);

        if (execv(av[0],av) == -1) {
            perror("execv: ");
        }
        exit(1);
    }

    close(pipefd[1]);
    dup2(pipefd[0], 0);
    close(pipefd[0]);

    char *av[] = {
		"/usr/bin/tr",
		"-d",
		"_",
		NULL,
	};
    
    if (execv(av[0],av) == -1) {
        perror("execv: ");
    }
    return (0);
}
