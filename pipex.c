/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/15 17:38:56 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pipex.h"

void	perror_message(char *parts)
{
		perror("%s", parts);
		close(infile);
		_exit(EXIT_FAILURE);
}

void	chiled_process(int argc, char *envp[], int *infile)
{
	int outfile;
	int fd_judge;

	fd_judge = 0;
	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("chiled_prrocess : fd_infile read");
		_exit(EXIT_FAILURE);
	}
	fd_judge = dup2(fd, 1);
	if (fd_judge > 0)
	{
		perror("dup2 file1");
		close(infile);
		_exit(EXIT_FAILURE);
	}
	fd_judge = dup2(outfile, 0);
	if (fd_judge > 0)
	{
		perror("dup2 file1");
		close(outfile);
		_exit(EXIT_FAILURE);
	}
	close(infile);
	
}

int main()
{
    int fd[2];
    pid_t pid;

    if (argc != 5)
    {/*引数が正しくない旨のコメントを表示させる*/
        perror("Bad arguments");
        return 0;
    }
    if (pipe(fd) == -1)
    {/*pipeの作成が失敗したら*/
        perror("pipe"); 
        exit (1);
    }
    pid = fork();
    if (pid == -1)
    {/*forkに失敗*/
        perror("fork");
        exit (1);
    }    
    else if (pid == 0)
    {/* forkに成功し、子プロセスとして動く */
        chiled_process(argv, envp, fd);
        exit(0);
    }
	/* forkに成功し、親プロセスに返される（数値は子プロセスのプロセスID） */
}
