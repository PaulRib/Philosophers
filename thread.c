/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:10:57 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/20 19:05:53 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	close_all_thread(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->nb_philo)
	{
		if (pthread_join(monitor->philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(monitor->checker, NULL) != 0)
		return (-1);
	return (0);
}

int	start_all_thread(t_monitor *monitor)
{
	int	i;

	i = 0;
	monitor->start = get_actual_time();
	while (i < monitor->nb_philo)
	{
		monitor->philo[i].last_meal = monitor->start;
		if (pthread_create(&monitor->philo[i].thread, NULL, jcvd_routine,
				(void *)&monitor->philo[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&monitor->checker, NULL, monitoring,
			(void *)monitor) != 0)
		return (-1);
	if (close_all_thread(monitor) == -1)
		return (-1);
	return (0);
}
