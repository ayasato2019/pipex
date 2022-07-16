/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/16 15:36:23 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pipex.h"

void	file_duplicate(int *infile, int outfile)
{
	int fd_judge;

	fd_judge = dup2(*infile, 1);
	if (fd_judge > 0)
	{
		perror("dup2 file1");
		close(*infile);
		_exit(EXIT_FAILURE);
	}
	fd_judge = dup2(outfile, 0);
	if (fd_judge > 0)
	{
		perror("dup2 file2");
		close(outfile);
		_exit(EXIT_FAILURE);
	}
}

void	chiled_process(char *argv[], char *envp[], int *infile)
{
	int outfile;

	outfile = open(argv[1], O_RDONLY, 0777);
	if (outfile == -1)
	{
		perror("chiled_prrocess infile open");
		exit(EXIT_FAILURE);
	}
	file_duplicate(infile, outfile);
	close(*infile);
	execve("./", &argv[2], envp);
}

void	parent_prosess(char *argv[], char *envp[], int *infile)
{
	int	outfile;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		perror("chiled_prrocess : fd_infile read");
		_exit(EXIT_FAILURE);
	}
	file_duplicate(infile, outfile);
	close(*infile);
	execve("./", &argv[3], envp);
}

int main(int argc, char *argv[], char *envp[])
{
    int fd[2];
    pid_t pid;

/*	引数の数を確認	*/
    if (argc != 5)
    {
        perror("Bad arguments");
        return 0;
    }
/*	pipeでファイルを生成する	*/
    if (pipe(fd) == -1)
    {
        perror("pipe"); 
        exit (1);
    }
/*	forkで子プロセスを生成する	*/
    pid = fork();
    if (pid == -1)/*forkに失敗*/
    {
        perror("fork");
        exit (1);
    }    
    else if (pid == 0)/* forkに成功し、子プロセスとして動く */
    {
        chiled_process(argv, envp, fd);
        exit(0);
    }
	/* forkに成功し、親プロセスに返される（数値は子プロセスのプロセスID） */
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, fd);
	return (0);
}
