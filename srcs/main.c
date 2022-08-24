/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:55:01 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/24 23:48:36 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	// int		status;
	pid_t	pid;
	int		i;
	char	**cmd_1;

	i = 0;
	if (argc != 5)
		set_perror("Bad arguments", EXIT_FAILURE);
	if (pipe(fd) == -1)
		set_perror("pipe", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		set_perror("fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		first_process(argv, fd);
	}
	else
	{
		recursive_fork(argc, argv, envp, i);
		if (dup2(fd[READ], STDIN_FILENO) == -1)
			set_perror("fd[0] dup", EXIT_FAILURE);
		close(fd[WRITE]);
		close(fd[READ]);
		cmd_1 = get_command(&argv[2]);
		make_cmd_filepath(envp, cmd_1);
	}
	return (0);
}
/*
	方針

	子プロセスの中でforkを繰り返して、
	mainの親プロセスはwaiteする
*/