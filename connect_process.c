/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:15:35 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/18 15:17:01 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	connect_infile(char **argv, char **envp, int *fd)
{
	int		fd_infile;
	int		i;

	i = 0;
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		set_perror("child process infile open", EXIT_FAILURE);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		set_perror("child process fd[1] dup", EXIT_FAILURE);
	close(fd_infile);
	return (0);
}

void	connect_pipe(int *fd)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	close(fd[1]);
}

void	connect_outfile(char **argv, int *fd)
{
	int		fd_outfile;

	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd[1]);
	if (fd_outfile == -1)
		set_perror("outfile open", EXIT_FAILURE);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		set_perror("outfile dup", EXIT_FAILURE);
	close(fd_outfile);
}
