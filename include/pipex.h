/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:16:23 by aysato            #+#    #+#             */
/*   Updated: 2022/08/18 15:35:04 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# include "libft.h"

//main.c
int		main(int argc, char **argv, char **envp);

//list_process.c
void	process_cmd1(int fd[2], char **argv, char **envp,
						char **cmd_1,char *filepath);
void	process_cmd2(int fd[2], char **argv, char **envp,
						char **cmd_2,char *filepath);
void	recursive_fork(int argc, char **argv, char **envp, int i);

//connect_process.c
void	connect_infile(char **argv, char **envp, int *fd);
void	connect_pipe(int *fd);
void	connect_outfile(char **argv, int *fd);

//set_cmd.c
void	make_cmd_filepath(char **envp, char **cmd);
int	cheack_access_status(char *file);
char	*check_filepath(char **filepath, char *cmd);
char	**get_filepath(char **envp, char **cmd);
char	**get_command(char **argv);

//set_exceve.c
void	try_execve(char **envp, char **cmd);

#endif