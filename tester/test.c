#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

void	process_1st(int i)
{
		printf("child:%d\n",i);
		exit(0);
}
void	process_2st(pid_t *pid, int i)
{
	int		status;
	i = 3;
	while(i-- != 0){
		waitpid(*pid, &status, 0);
		printf("parent:%d\n",i);
	}
}

int main()
{
	pid_t pid[3];
	int		i;

	i = 0;
	while(i < 3 && (pid[i] = fork()) > 0)
		i++;
	if( i == 3 ){
		process_2st(pid, i);
	}else if( pid[i] == 0){
		process_1st(i);
	}else{
		perror("child process") ;
		exit(0);
	}
	return 0;
}