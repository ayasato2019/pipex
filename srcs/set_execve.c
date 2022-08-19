/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:52:17 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/19 20:30:16 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	try_execve(char **envp, char **cmd)
{
	char	**filepath;
	char	*cmd_filepath;

	filepath = get_filepath(envp, cmd);
	cmd_filepath = check_filepath(filepath, cmd[0]);
	if (execve(cmd_filepath, cmd, envp) == -1)
		set_perror_allfree(EXIT_FAILURE, cmd, filepath, cmd_filepath);
}
