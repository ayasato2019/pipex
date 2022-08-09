/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:14:51 by satouaya          #+#    #+#             */
/*   Updated: 2022/08/09 09:14:55 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*temp_s1;
	const unsigned char	*temp_s2;

	temp_s1 = (const unsigned char *)s1;
	temp_s2 = (const unsigned char *)s2;
	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*temp_s1 != *temp_s2)
			return (*temp_s1 - *temp_s2);
		else if (*temp_s1 == *temp_s2 && n)
		{
			temp_s1++;
			temp_s2++;
		}
	}
	return (0);
}
