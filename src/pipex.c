/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/08/15 08:32:48 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	process_parents(pid_t *pid, char **envp)
{
	int		status;
}

void	process_fork(int argc, int i)
{
	pid_t	*pid;

	if (i == (argc - 3))
		//process_parents
	else
	{
		process_pipe();
		pid = fork();
		if (pid == 0)
		{
			process_dup2();
			process_fork(argc, i + 1);
		}
		else if (pid > 0)
		{
			process_dup2();
			try_execve();
		}	
		else
			set_perror("fork", EXIT_FAILURE);
	}
}

int	*process_pipe(void)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		set_perror("pipe", EXIT_FAILURE);
	else
		return (fd_pipe);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		i;
	char	**cmd;

	if (argc != 5)
		set_perror("Bad arguments", EXIT_FAILURE);
	process_pipe();
	process_fork(argc, i);
	return (0);
}
