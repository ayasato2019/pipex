/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:55:01 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/25 22:40:48 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
		set_perror("Bad arguments", EXIT_FAILURE);
	if (pipe(fd) == -1)
		set_perror("pipe", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		set_perror("fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		first_process(argv, envp, fd);
	}
	else
	{
		recursive_fork(argv, envp, fd);
		if (waitpid(pid, &status, 0) == -1)
			set_perror("waitpid", EXIT_FAILURE);
	}
	return (0);
}
/*
	方針

	子プロセスの中でforkを繰り返して、
	mainの親プロセスはwaiteする
*/