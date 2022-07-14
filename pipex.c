/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/14 12:12:04 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define LOG_FILE_PATH "./test.log"
// // int main(void){
// //     int fd,size;
// //     char buf[128];

// //     fd = open(LOG_FILE_PATH, (O_RDONLY), 0664);

// //     if(fd < 0)
// //         return -1;
// //     close(fd);
// //     return 0;
// // }

// int main(int argc, char *argv[])
// {
//     int pipefd[2];
//     pid_t cpid;
//     char buf;
    
//     if (argc != 2)
//     {
//         fprintf(stderr,"Usage:%s<string>\n",argv[0]);
//         exit(EXIT_FAILURE);
//     }
    
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }
    
//     cpid = fork();
//     if (cpid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (cpid == 0) {
//         //小プロセルがパイプから読み込む
//         close(pipefd[1]);//使わないwrite側はクローズする
//         while (read(pipefd[0],&buf,1) > 0)
//             write(STDOUT_FILENO,&buf,1);
//         write(STDOUT_FILENO, "\n", 1);
//         close(pipefd[0]);
//         _exit(EXIT_SUCCESS);
//     } else {//親プロセスはargv[1]をパイプへ書き込む
//         close(pipefd[0]);//使用しないread側はクローズする
//         write(pipefd[1],argv[1],strlen(argv[1]));//読み込み側がEOFに出会う
//         close(pipefd[1]);//子プロセスを待つ
//         wait(NULL);
//         exit(EXIT_SUCCESS);
//     }
// }

#include <stdio.h>

int main()
{
    // pid_t pid;
    // int iStatus;

    // if((pid = fork()) == 1)//fork失敗
    // {
    //     perror("fork()");
    //     return 1;
    // }
    // else if (pid > 0) //親プロセスの処理
    // {
    //     printf("I am parent process...(id = %d)\n", getpid());
    //     wait(&iStatus);

    //     if (iStatus & 0x00ff) //正常終了かどうか
    //         printf("child process has finished(status=%d)\n",(iStatus >> 4) & 0x00ff);
    //     else
    //         printf("child process has received signal(%d)\n", iStatus & 0x00ff);
    // }
    // else
    // {
    //     printf("I an child process...(id = %d)\n",getpid());
    //     printf("Plead enter key...");
    //     getchar();
        
    //     if (execlp("ls","ls", NULL) == -1)
    //     {
    //         perror("execlp()");
    //         return 2;
    //     }
    //     return 0;
    // }
    // return 0;
}