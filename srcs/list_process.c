/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/08/25 22:41:09 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(char **argv, char **envp, int *fd)
{
	int		fd_infile;
	char	**cmd;

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
	cmd = get_command(&argv[2]);
	make_cmd_filepath(envp, cmd);
}

void	last_process(char **argv, char **envp, int *fd)
{
	int		fd_outfile;
	char	**cmd;

	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		set_perror("outfile open", EXIT_FAILURE);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		set_perror("outfile dup", EXIT_FAILURE);
	close(fd_outfile);
	if (dup2(fd[READ], STDIN_FILENO) == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	close(fd[WRITE]);
	close(fd[READ]);
	cmd = get_command(&argv[3]);
	make_cmd_filepath(envp, cmd);
}

void	recursive_fork(char **argv, char **envp, int *fd)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		set_perror("fork", EXIT_FAILURE);
	if (pid2 == 0)
		last_process(argv, envp, fd);
	else
	{
		close(fd[WRITE]);
		if (dup2(fd[READ], STDIN_FILENO) == -1)
			set_perror("fd[REAS] dup", EXIT_FAILURE);
		close(fd[READ]);
	}
}
