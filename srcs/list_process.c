/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/08/25 14:19:12 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(char **argv, int *fd)
{
	int		fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		set_perror("child process infile open", EXIT_FAILURE);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		set_perror("child process fd[1] dup", EXIT_FAILURE);
	close(fd_infile);
	if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	close(fd[WRITE]);
	close(fd[READ]);
}

// void	middle_process(int *fd)
// {
// 	if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
// 		set_perror("dup2", EXIT_FAILURE);
// 	close(fd[WRITE]);
// 	if (dup2(fd[READ], STDIN_FILENO) == -1)
// 		set_perror("fd[READ] dup", EXIT_FAILURE);
// 	close(fd[READ]);
// }

void	last_process(char **argv, int *fd)
{
	int		fd_outfile;

	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd[WRITE]);
	close(fd[READ]);
	if (fd_outfile == -1)
		set_perror("outfile open", EXIT_FAILURE);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		set_perror("outfile dup", EXIT_FAILURE);
	close(fd_outfile);
}

void	recursive_fork(char **argv, char **envp)
{
	int		new_fd[2];
	pid_t	pid2;
	char	**cmd;

	if (pipe(new_fd) == -1)
		set_perror("pipe", EXIT_FAILURE);
	pid2 = fork();
	if (pid2 == -1)
		set_perror("fork", EXIT_FAILURE);
	if (pid2 == 0)
	{
		last_process(argv, new_fd);
		close(new_fd[READ]);
		cmd = get_command(&argv[3]);
		make_cmd_filepath(envp, cmd);
	}
	else
	{
		if (dup2(new_fd[READ], STDIN_FILENO) == -1)
			set_perror("fd[REAS] dup", EXIT_FAILURE);
		close(new_fd[READ]);
	}
}
