/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:52:17 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/22 10:15:46 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_command(char **argv)
{
	char	**cmd;

	cmd = ft_split((*argv), ' ');
	if (!cmd)
		set_perror("error", EXIT_FAILURE);
	return (cmd);
}
