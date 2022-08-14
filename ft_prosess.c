/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prosess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:32:56 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/12 15:14:09 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**process_1st(char **argv, char **envp, int *fd_pipe)
{
	int		fd_infile;
	int		i;
	char	**cmd;

	i = 0;
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		set_perror("child process infile open", EXIT_FAILURE);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		set_perror("child process fd[1] dup", EXIT_FAILURE);
	close(fd_infile);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		set_perror("child process infile dup", EXIT_FAILURE);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	cmd = get_command(&argv[2]);
	return (cmd);
}

char	**process_2st(char **argv, char **envp, int *fd_pipe)
{
	int		fd_outfile;
	int		i;
	char	**cmd;

	i = 0;
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		set_perror("outfile open", EXIT_FAILURE);
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDOUT_FILENO) == -1)
		set_perror("outfile dup", EXIT_FAILURE);
	close(fd_outfile);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		set_perror("fd_pipe[0] dup", EXIT_FAILURE);
	close(fd_pipe[0]);
	cmd = get_command(&argv[3]);
	return (cmd);
}

