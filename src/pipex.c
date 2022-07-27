/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/27 13:45:06 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	fd_infile;
	int	status;
	int	i;

	i = 0;
	fd_infile = open(argv[1], O_RDONLY, 0777);
	if (fd_infile == -1)
		set_perror("child process infile open", EXIT_FAILURE);
	status = dup2(fd_infile, STDIN_FILENO);
	if (status == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	status = dup2(fd[1], STDOUT_FILENO);
	if (status == -1)
		set_perror("child process fd[1] dup", EXIT_FAILURE);
	close(fd[0]);
	while(envp[i])
	{
		execve(envp[i], &argv[2], envp);
		i++;
	}
	printf("通過確認 cp");
	// if (execve("/bin/ls", "li -a", envp) == -1)
	// {
	// 	perror("child process execve");
	// 	_exit(EXIT_FAILURE);
	// }
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fd_outfile;
	int	status;
	int	i;

	i = 0;
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_outfile == -1)
		set_perror("outfile fd", EXIT_FAILURE);
	status = dup2(fd_outfile, STDOUT_FILENO);
	if (status == -1)
		set_perror("parent process outfile dup", EXIT_FAILURE);
	status = dup2(fd[0], STDIN_FILENO);
	if (status == -1)
		set_perror("parent process fd[0] dupe", EXIT_FAILURE);
	close(fd[1]);
	printf("通過確認 pp");
	while(envp[i])
	{
		execve(envp[i], &argv[2], envp);
		i++;
	}
	// if (execve("/usr/bin/wc", "wc -l", envp) == -1)
	// {
	// 	set_perror("parent process execve", EXIT_FAILURE);
	// }
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
	printf("通過確認1");
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
	printf("通過確認2");
	return (0);
}
