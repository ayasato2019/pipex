/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:55:01 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/25 13:28:50 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	int		i;
	char	**cmd_1;
	int		cmd_count;

	i = 0;
	cmd_count = (argc - 2);
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
		recursive_fork(argc, argv, envp, i);
	}
	else
	{
		if (dup2(fd[READ], STDIN_FILENO) == -1)
			set_perror("fd[REAS] dup", EXIT_FAILURE);
		close(fd[READ]);
		if (waitpid(pid, &status, 0) == -1)
			set_perror("waitpid", EXIT_FAILURE);
		cmd_1 = get_command(&argv[i + 2]);
		make_cmd_filepath(envp, cmd_1);
	}
	return (0);
}
/*
	方針

	子プロセスの中でforkを繰り返して、
	mainの親プロセスはwaiteする
*/