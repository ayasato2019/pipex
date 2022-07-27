/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:52:17 by satouaya          #+#    #+#             */
/*   Updated: 2022/07/27 13:42:07 by satouaya         ###   ########.fr       */
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

	while(ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		set_perror("get_filepath strncmp", EXIT_FAILURE);
	filepath = ft_split((*envp) + 5, ':');
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
// 	// char    **cmd;
	
// 	i = 0;
// 	if (!argc)
// 		return 0;
// 	// cmd = get_command(&argv[2]);
// 	envp = get_filepath(envp);
// 	i = 0;
// 	while(envp[i])
// 	{
// 		execve(envp[i], &argv[2], envp);
// 		i++;
// 	}
// 	return (0);
// }