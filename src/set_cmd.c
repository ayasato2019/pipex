/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:52:17 by satouaya          #+#    #+#             */
/*   Updated: 2022/07/27 15:31:06 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// static char	**ft_free(char **container)
// {
// 	size_t	i;

// 	i = 0;
// 	while (container[i])
// 		free(container[i++]);
// 	free(container);
// 	return (NULL);
// }
void	set_perror(char *cmt, int status)
{
	perror(cmt);
	exit(status);
}

char	**get_filepath(char **envp)
{
	char	**filepath;
	int		i;

	i = 0;
	while(ft_strncmp(*envp, "PATH=", 5))
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
	if(!cmd)
	{
		printf("error");
		return (NULL);
	}
	return (cmd);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int     i;
// 	char    **cmd;
// 	char    **filepath;
	
// 	i = 0;
// 	if (!argc)
// 		return 0;
// 	cmd = get_command(&argv[1]);
// 	filepath = get_filepath(envp);
// 	i = 0;
// 	while(filepath[i])
// 	{
// 		printf("envp: %s\n", ft_strjoin(filepath[i], *cmd));
// 		execve(ft_strjoin(filepath[i], *cmd), cmd, envp);
// 		i++;
// 	}
// 	printf("error");
// 	exit(EXIT_FAILURE);
// 	return (0);
// }