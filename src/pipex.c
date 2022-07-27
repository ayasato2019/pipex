/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/27 15:29:11 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	fd_infile;
	int	i;
	char    **cmd;
	char    **filepath;

	i = 0;
	fd_infile = open(argv[1], O_RDONLY, 0777);
	if (fd_infile == -1)
		set_perror("child process infile open", EXIT_FAILURE);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	close(fd[0]);
	// close(fd_infile);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		set_perror("child process fd[1] dup", EXIT_FAILURE);
	// close(fd[1]);
	cmd = get_command(&argv[2]);
	filepath = get_filepath(envp);
	while(filepath[i])
	{
		execve(ft_strjoin(filepath[i], *cmd), cmd, envp);
		i++;
	}
	// if (execve("/bin/cat", "cat", envp) == -1)
	// {
	// }
	perror("child process execve");
	_exit(EXIT_FAILURE);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fd_outfile;
	int	i;
	char    **cmd;
	char    **filepath;

	i = 0;
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_outfile == -1)
		set_perror("outfile fd", EXIT_FAILURE);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		set_perror("parent process outfile dup", EXIT_FAILURE);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		set_perror("parent process fd[0] dup", EXIT_FAILURE);
	// close(fd_outfile);
	close(fd[0]);
	cmd = get_command(&argv[3]);
	filepath = get_filepath(envp);
	while(filepath[i])
	{
		execve(ft_strjoin(filepath[i], *cmd), cmd, envp);
		i++;
	}
	// if (execve("/usr/bin/wc", "wc", envp) == -1)
	// {
	// }
	set_perror("parent process execve", EXIT_FAILURE);
	exit(EXIT_FAILURE);
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
	{
		child_process(argv, envp, fd);
	}
	else
	{
		waitpid(pid, &status, 0);
		parent_process(argv, envp, fd);
	}
	return (0);
}
