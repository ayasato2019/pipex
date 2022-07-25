/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/26 05:49:31 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_perror(char *cmt, int status)
{
	perror(cmt);
	exit(status);
}

// char	*get_filepath(char **envp)
// {
// 	char	*temp;
// 	char	**filepath;
// 	size_t	i;

// 	while(ft_strncmp(*envp, "PATH=", 5))
// 		envp++;
// 	if (!*envp)
// 		set_perror("get_filepath strncmp", EXIT_FAILURE);
// 	filepath = ft_split((*envp) + 5, ':');
// 	i = 0;
// 	while (filepath[i])
// 	{
// 		temp = filepath[i];
// 		i++;
// 	}
// 	return (filepath);
// }

void	child_process(char **argv, char **envp, int *fd)
{
	int	fd_infile;
	int	status;

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
	if (execve("/bin/ls", &argv[2], envp) == -1)
	{
		printf("&argv[2] child : %c", *argv[2]);
		perror("child process execve");
		_exit(EXIT_FAILURE);
	}
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fd_outfile;
	int	status;

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
	if (execve("/usr/bin/wc", &argv[3], envp) == -1)
	{
		printf("&argv[2] parent : %c", *argv[2]);
		set_perror("parent process execve", EXIT_FAILURE);
	}
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
