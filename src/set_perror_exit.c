/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:38:49 by satouaya          #+#    #+#             */
/*   Updated: 2022/07/28 22:45:59 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_perror(char *cmt, int status)
{
	perror(cmt);
	exit(status);
}

void	set_free(char ***dst, char *src)
{
	size_t	i;

	if (*dst == NULL)
		return;
	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(*dst);
	**dst = src;
}

void	set_exit(char **cmd, char **filepath, int status)
{
	size_t	i;

	i = 0;
	ft_printf("no such file or directory:", *cmd);
	ft_free(&cmd, NULL);
	ft_free(&filepath, NULL);
	exit(status);
}