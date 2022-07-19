/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/19 23:31:54 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pipex.h"

void	exite_process(int type, int status)//const char *strで持ってこれないか
{
	if (type == 0)/*引数が対応していない*/
		perror("Bad arguments");
	if (type == 1)/*pipe失敗*/
		perror("fork");
	if (type == 2)/*forkに失敗*/
		perror("fork");
	if (type == 3)/*childe process*/
		perror("chiled_process => infile open");
	if (type == 4)/*parent process*/
		perror("parent_process => outfile open");
	// if (type == 5)/*引数が対応していない*/
	// 	perror("Bad arguments");
	exit(status);
}

void	chiled_process(char **argv, char **envp, int *infile)
{
	int outfile;

	*infile = open(argv[1], O_RDONLY, 0777);
	if (*infile == -1)
		exite_process(3, EXIT_FAILURE);
	fd_duplicate(infile, outfile);
	close(outfile);
	execve("./", &argv[2], envp);
}

void	parent_prosess(char **argv, char **envp, int *outfile)
{
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		exite_process(4, EXIT_FAILURE);
	dup2(outfile);
	execve("./", &argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];//pipe[0]は書き込み用 pipe[1]は読み込み用
	pid_t pid;//forkで複製したプロセス

	if (argc != 5)
		exite_process(0, -1);
	if (pipe(fd) == -1)
		exite_process(1, 1);
	pid = fork();
	if (pid == -1)
		exite_process(2, EXIT_FAILURE);
	else if (pid == 0)
	{
		chiled_process(argv, envp, fd[0]);
		exit(0);
	}
	else 
	{
		waitpid(pid, NULL, 0);
		close(fd[0]);
		parent_prosess(argv, envp, fd[1]);
	}
	return (0);
}
