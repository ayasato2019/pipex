/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/08/15 08:06:09 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	process_parents(pid_t *pid, char **envp)
{
	int		status;

	if (waitpid(pid[2], &status, 0) != -1)
	{
		if (waitpid(pid[1], &status, 0) != -1)
		{
			if (waitpid(pid[0], &status, 0) != -1)
			{
				try_execve(envp, cmd);
			}
			else
				set_perror("wait 1", EXIT_FAILURE);
	}
	else
		set_perror("wait 1", EXIT_FAILURE);
}

void	process_fork(int i)
{
	pid_t	*pid;

	pid[i] = fork();
	while (pid[i] <= (argc - 3))
	{
		if (pid == 0)
			cmd = process_1st(argv, envp, fd_pipe);
		else if (pid > 0)
			process_parents(pid, envp);
		else
			set_perror("fork", EXIT_FAILURE);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_pipe[2];
	int		status;
	int		i;
	char	**cmd;

	if (argc != 5)
		set_perror("Bad arguments", EXIT_FAILURE);
	if (pipe(fd_pipe) == -1)
		set_perror("pipe", EXIT_FAILURE);
	process_fork(pid_t *pid, int i);
	return (0);
}
