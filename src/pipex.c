/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/08/09 10:01:49 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	make_cmd_filepath(char **envp, char **cmd)
{
	char	**filepath;
	char	*cmd_filepath;

	filepath = get_filepath(envp, cmd);
	cmd_filepath = check_filepath(filepath, cmd[0]);
	if (execve(cmd_filepath, cmd, envp) == -1)
		set_perror_allfree(EXIT_FAILURE, cmd, filepath, cmd_filepath);
}

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
		child_process(argv, envp, fd);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			set_perror("waitpid", EXIT_FAILURE);
		parent_process(argv, envp, fd);
	}
	return (0);
}
