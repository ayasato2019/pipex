/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/08/20 15:26:28 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		fd_infile;
	int		i;
	char	**cmd;

	i = 0;
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		set_perror("child process infile open", EXIT_FAILURE);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		set_perror("child process fd[1] dup", EXIT_FAILURE);
	close(fd_infile);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	close(fd[1]);
	close(fd[0]);
	cmd = get_command(&argv[2]);
	make_cmd_filepath(envp, cmd);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		fd_outfile;
	int		i;
	char	**cmd;

	i = 0;
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd[1]);
	if (fd_outfile == -1)
		set_perror("outfile open", EXIT_FAILURE);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		set_perror("outfile dup", EXIT_FAILURE);
	close(fd_outfile);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		set_perror("fd[0] dup", EXIT_FAILURE);
	close(fd[0]);
	cmd = get_command(&argv[3]);
	make_cmd_filepath(envp, cmd);
}

