/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:21:22 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/11 17:22:41 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi_philo(char *nptr)
{
	int	i;
	int	nb;
	int	before;

	nb = 0;
	i = 0;
	if (nptr[0] == '-')
		return (-1);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		before = nb;
		nb *= 10;
		nb += nptr[i] - '0';
		if (before > nb)
			return (-1);
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	return (nb);
}
