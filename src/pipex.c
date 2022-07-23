/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/21 21:42:03 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_filepath(char **envp)
{
	char	*temp;
	char	*filepath;
	size_t	i;

	i = 0;
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return NULL;
	filepath = *(ft_split((*envp) + 5, ':'));
	if (filepath == NULL)
	{
		perror("get filepath");
		exit(EXIT_FAILURE);
	}
	while (filepath[i])
	{
		temp = &filepath[i];
		filepath[i] = *(ft_strjoin(&filepath[i], "/"));
		if (!filepath[i])
		{
			perror("get filepath");
			exit(EXIT_FAILURE);
		}
		i++;
		free(temp);
	}
	return (filepath);
}

/*　
	---fd[0] = read
	---fd[1] = wrire
	
	---[process1]fd1(stdout) -> write[pipe]read -> fd0(stdin)[process]

	[infile] -> [STDIN]  infileのFDとして標準入力を使用する
	[fd[1]]  -> [STDOUT] パイプの書き込み口として、標準出力を使用する
	[fd[0]]  -> [close] 　パイプの読み込み口は使わないのでclose
	
	デフォルトのパイプ容量は 65,536 バイト、それ以前のバージョンでは、パイプの容量はシステムのページサイズと同一（例えば i386 の場合は 4,096 バイト）
　*/
void	child_process(char **argv, char **envp, int *fd)
{
	int fd_infile;
	int status;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		perror("child process infile open");
		_exit(EXIT_FAILURE);
	}
	status = dup2(fd_infile, STDIN_FILENO);
	if (status == -1)
	{
		perror("child process infile dup");
		_exit(EXIT_FAILURE);
	}
	status = dup2(fd[1], STDOUT_FILENO);
	if (status == -1)
	{
		perror("child process fd[1] dup");
		_exit(EXIT_FAILURE);
	}
	printf("%s\n", *envp);
	// if (execve("./", &argv[2], envp) == -1)
	// {
	// 	perror("child process execve");
	// 	_exit(EXIT_FAILURE);
	// }
}

/*　
	---fd[0] = read
	---fd[1] = wrire
	
	---[process1]fd1(stdout) -> write[pipe]read -> fd0(stdin)[process]

	[outfile] -> [STDOUT]  outfileのFDとして標準出力を使用する
	[fd[0]]   -> [STDIN]   パイプの読み込み口として、標準入力を使用する
	[fd[1]]   -> [close]  　パイプの書き込み口は使わないのでclose
　*/
void	parent_process(char **argv, char **envp, int *fd)
{
	int fd_outfile;
	int status;

	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
	{
		perror("outfile fd");
		exit(EXIT_FAILURE);
	}
	status = dup2(fd_outfile, STDOUT_FILENO);
	if (status == -1)
	{
		perror("parent process outfile dup");
		exit(EXIT_FAILURE);
	}
	status = dup2(fd[0], STDIN_FILENO);
	if (status == -1)
	{
		perror("parent process fd[0] dup");
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	printf("%s\n", *envp);
	// if (execve("./", &argv[2], envp) == -1)
	// {
	// 	perror("execve");
	// 	_exit(EXIT_FAILURE);
	// }
}

int	main (int argc, char **argv, char **envp)
{
	int fd[2];
	int status;
	pid_t pid;

	printf("%s\n", *envp);
	if (argc != 5)
	{
		perror("Bad arguments");
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		child_process(argv, envp, fd);
	}
	else
	{
		waitpid(pid, &status, 0);
		// parent_process(argv, envp, fd);
	}
	return (0);
}
