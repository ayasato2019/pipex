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

char	*get_filepath(char **envp)
{
	char	*temp;
	char	*filepath;
	size_t	i;

	i = 0;
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	filepath = *(ft_split((*envp) + 5, ':'));
	if (filepath == NULL)
		set_perror("get filepath", EXIT_FAILURE);
	while (filepath[i])
	{
		temp = &filepath[i];
		filepath[i] = *(ft_strjoin(&filepath[i], "/"));
		if (!filepath[i])
			set_perror("ft_strjoin", EXIT_FAILURE);
		i++;
		free(temp);
	}
	return (filepath);
}

int main(int argc, char **argv, char **envp)
{

	if (argc != 5)
        return 0;
	printf("main: %s\n", *envp);
    prentf("main :%s", *argv);
    prentf("main :%s", get_filepath(envp));
    return 0;
}