/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:04:29 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/20 19:00:51 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (-1);
	memset(monitor, 0, sizeof(t_monitor));
	if (check_and_parse(monitor, argc, argv) == -1)
	{
		ft_putstr_fd("Parsing error : only work with 4 or 5", 2);
		ft_putstr_fd(" positive integers as argument\n", 2);
		free(monitor);
		return (-1);
	}
	if (init_all(monitor) == -1)
		return (-1);
	if (start_all_thread(monitor) == -1)
	{
		free_all(monitor);
		return (-1);
	}
	free_all(monitor);
}
