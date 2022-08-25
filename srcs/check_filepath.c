/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filepath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:56:19 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/22 18:39:30 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_cmd_filepath(char **envp, char **cmd)
{
	char	**filepath;
	char	*cmd_filepath;

	filepath = get_filepath(envp, cmd);
	cmd_filepath = check_filepath(filepath, cmd[0]);
	if (execve(cmd_filepath, cmd, envp) == -1)
		set_perror_allfree(-1, cmd, filepath, cmd_filepath);
}

int	get_status(char *file)
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
		if (get_status(filepath[i]) >= 0)
			return (filepath[i]);
		if (filepath[i] == NULL)
			set_perror("malloc", -1);
		i++;
	}
	return (ft_strdup("-1"));
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
		set_perror("get_filepath strncmp", -1);
	filepath = ft_split((*envp) + 5, ':');
	while (filepath[i])
	{
		temp = filepath[i];
		filepath[i] = ft_strjoin(filepath[i], "/");
		if (filepath[i] == NULL)
			set_perror_allfree(-1, cmd, filepath, NULL);
		free(temp);
		if (filepath[i] == NULL)
			set_perror("malloc", -1);
		i++;
	}
	return (filepath);
}
