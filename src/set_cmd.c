/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:52:17 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/09 09:43:03 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
			set_perror("malloc", EXIT_FAILURE);
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

/*int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
	char	**filepath;
	char	*cmd_filepath;
	// int i;

	if (!argc)
		return 0;
	cmd = get_command(&argv[1]);
	filepath = get_filepath(envp);
	if (!filepath)
		set_perror("can not get the filepath", EXIT_FAILURE);
	i = 0;
	while (filepath[i])
	{
		printf("main filepath : %s\n", filepath[i]);
		i++;
	}
	i = 0;
	while (cmd[i])
	{
		printf("main cmd : %s\n", cmd[i]);
		i++;
	}
	cmd_filepath = check_filepath(filepath, cmd[0]);
	printf("cmd_filepath %s\n", cmd_filepath);
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}*/