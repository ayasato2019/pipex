/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:16:23 by aysato            #+#    #+#             */
/*   Updated: 2022/08/02 09:04:27 by satouaya         ###   ########.fr       */
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
// # include "../libft/libft.h" 

int		main(int argc, char **argv, char **envp);
void	child_process(char **argv, char **envp, int *fd);
void	parent_process(char **argv, char **envp, int *fd);
char	**get_command(char **argv);
char	**get_filepath(char **envp);
char	*check_filepath(char **filepath, char *cmd);
int		get_status(char *file);
void	set_perror(char *cmt, int status);
void	set_perror_allfree(int status, char **cnt,
			char **cnt2, char *cnt3);
void	set_free(char ***dst, char *src);
void	ft_free(char **dst, char *src);

#endif