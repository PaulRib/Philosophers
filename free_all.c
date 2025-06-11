/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:56:50 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/11 17:45:52 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_mutex(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->nb_philo)
	{
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	if (monitor->philo)
		pthread_mutex_destroy(&monitor->philo->meal_mutex);
	pthread_mutex_destroy(&monitor->dead_mutex);
}

int	free_all(t_monitor *monitor)
{
	destroy_all_mutex(monitor);
	if (monitor->forks)
		free(monitor->forks);
	if (monitor->philo)
		free(monitor->philo);
	free(monitor);
	return (-1);
}
