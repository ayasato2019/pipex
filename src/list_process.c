/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:17:25 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/18 15:31:51 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_cmd1(int fd[2], char **argv, char **envp,
						char **cmd_1,char *filepath)
{
	connect_pipe(fd);
	connect_infile(argv, fd);
	filepath = get_filepath(envp, cmd_1);
	if (filepath == -1 || filepath =="-1")
		set_perror("get filepath", EXIT_FAILURE);
	try_execve(envp, cmd_1);
}	

void	process_cmd2(int fd[2], char **argv, char **envp,
						char **cmd_2,char *filepath)
{
	connect_pipe(fd);
	connect_outfile(argv, fd);
	filepath = get_filepath(envp, cmd_2);
	if (filepath == -1 || filepath =="-1")
		set_perror("get filepath", EXIT_FAILURE);
}	

void	recursive_fork(int argc, char **argv, char **envp, int i)
{
	pid_t	*pid2;
	int		fd[2];
	char	**cmd_1;
	char	**cmd_2;
	char	**filepath;

	cmd_1 = get_command(&argv[2]);
	cmd_2 = get_command(&argv[3]);
	if (i == (argc - 3))
		process_cmd2(fd[2], argv, envp, cmd_2, filepath);
	else
	{
		if (pipe(fd) == -1)
			set_perror("pipe", EXIT_FAILURE);
		pid2 = fork();
		if (pid2 == 0)
		{
			connect_pipe(fd);
			recursive_fork(argc, argv, envp, i + 1);
		}
		else if (pid2 > 0)
		{
			process_cmd1(fd[2], argv, envp, cmd_1, filepath);
			try_execve(envp, cmd_2);
		}
		else
			set_perror("fork", EXIT_FAILURE);
	}
}
