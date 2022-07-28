/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:38:49 by satouaya          #+#    #+#             */
/*   Updated: 2022/07/28 21:54:58 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_perror(char *cmt, int status)
{
	perror(cmt);
	exit(status);
}

void	ft_free(char **dst, char *src)
{
	free(*dst);
	*dst = src;
}

void	set_exit(char **cmd, char **filepath)
{
	perror(" no such file or directory:", *cmd);
	ft_free(cmd, NULL);
	ft_free(filepath, NULL);
}