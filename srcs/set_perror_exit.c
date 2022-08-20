/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:38:49 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/20 15:26:30 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_free(char ***dst, char *src)
{
	size_t	i;

	if (*dst == NULL)
		return ;
	i = 0;
	while (dst[0][i] != NULL)
	{
		free((*dst)[i]);
		i++;
	}
	free(*dst);
	**dst = src;
}

void	ft_free(char **dst, char *src)
{
	if (*dst == NULL)
		return ;
	free(*dst);
	*dst = src;
}

void	set_perror(char *cmt, int status)
{
	perror(cmt);
	exit(status);
}

void	set_perror_allfree(int status, char **cnt,
			char **cnt2, char *cnt3)
{
	int		i;

	i = 0;
	perror("execve");
	set_free(&cnt, NULL);
	set_free(&cnt2, NULL);
	ft_free(&cnt3, NULL);
	exit(status);
}
