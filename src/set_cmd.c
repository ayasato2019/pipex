/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:52:17 by satouaya          #+#    #+#             */
/*   Updated: 2022/07/28 23:39:06 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_filepath(char **envp)
{
	char	**filepath;
	size_t	i;

	i = 0;
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		set_perror("get_filepath strncmp", EXIT_FAILURE);
	filepath = ft_split((*envp) + 5, ':');
	while (filepath[i])
	{
		filepath[i] = ft_strjoin(filepath[i], "/");
		i++;
	}
	return (filepath);
}

char	**get_command(char **argv)
{
	char	**cmd;

	cmd = ft_split((*argv), ' ');
	if (!cmd)
	{
		set_perror("error");
		return (NULL);
	}
	return (cmd);
}
