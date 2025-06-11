/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:04:29 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/11 17:53:27 by pribolzi         ###   ########.fr       */
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
		ft_putstr_fd("Parsing error : only work with 4 or 5 arguments\n", 2);
		free(monitor);
		return (-1);
	}
	printf("NB PHILO : %d\nTIME TO DIE : %d\nTIME TO EAT : %d\nTIME TO SLEEP : %d\nNB MUST EAT : %d\n",
		monitor->nb_philo, monitor->time_to_die, monitor->time_to_eat, monitor->time_to_sleep, monitor->nb_must_eat);
}
