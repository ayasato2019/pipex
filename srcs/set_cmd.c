/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:52:17 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/19 20:21:03 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	make_cmd_filepath(char **envp, char **cmd)
{
	char	**filepath;
	char	*cmd_filepath;

	filepath = get_filepath(envp, cmd);
	cmd_filepath = check_filepath(filepath, cmd[0]);
	if (execve(cmd_filepath, cmd, envp) == -1)
		set_perror_allfree(EXIT_FAILURE, cmd, filepath, cmd_filepath);
}

int	cheack_access_status(char *file)
{
	if (access(file, X_OK) == 0)
		return (0);
	if (access(file, F_OK) == 0)
		return (1);
	return (-1);
}

char	*check_filepath(char **filepath, char *cmd)
{
	char	*temp;
	size_t	i;

	i = 0;
	while (filepath[i])
	{
		temp = filepath[i];
		filepath[i] = ft_strjoin(filepath[i], cmd);
		free(temp);
		if (cheack_access_status(filepath[i]) >= 0)
			return (filepath[i]);
		if (filepath[i] == NULL)
			set_perror("malloc", EXIT_FAILURE);
		i++;
	}
	return (NULL);
}

char	**get_filepath(char **envp, char **cmd)
{
	char	**filepath;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		set_perror("get_filepath strncmp", EXIT_FAILURE);
	filepath = ft_split((*envp) + 5, ':');
	while (filepath[i])
	{
		temp = filepath[i];
		filepath[i] = ft_strjoin(filepath[i], "/");
		if (filepath[i] == NULL)
			set_perror_allfree(EXIT_FAILURE, cmd, filepath, NULL);
		free(temp);
		if (filepath[i] == NULL)
			set_perror("malloc", EXIT_FAILURE);
		i++;
	}
	return (filepath);
}

char	**get_command(char **argv)
{
	char	**cmd;

	cmd = ft_split((*argv), ' ');
	if (!cmd)
		set_perror("error", EXIT_FAILURE);
	return (cmd);
}
