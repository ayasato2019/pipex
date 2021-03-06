/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:16:23 by aysato            #+#    #+#             */
/*   Updated: 2022/07/28 22:52:55 by satouaya         ###   ########.fr       */
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
# include "ft_printf.h" 

char	**get_filepath(char **envp);
char	**get_command(char **argv);
void	child_process(char **argv, char **envp, int *fd);
void	parent_process(char **argv, char **envp, int *fd);
int		main(int argc, char **argv, char **envp);
void	set_perror(char *cmt, int status);
void	set_exit(char **cmd, char **filepath, int status);
void	set_free(char ***dst, char *src);

#endif