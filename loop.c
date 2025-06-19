/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:36:05 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/19 17:28:18 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(t_philo *philo, t_monitor *monitor)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&monitor->forks[philo->left]);
		print_action(monitor, philo, "has taken a fork");
		pthread_mutex_lock(&monitor->forks[philo->right]);
		print_action(monitor, philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&monitor->forks[philo->right]);
		print_action(monitor, philo, "has taken a fork");
		pthread_mutex_lock(&monitor->forks[philo->left]);
		print_action(monitor, philo, "has taken a fork");
	}
	print_action(monitor, philo, "is eating");
	pthread_mutex_unlock(&monitor->forks[philo->left]);
	pthread_mutex_unlock(&monitor->forks[philo->right]);
	//increase all meal
	//mettre last time a jour
}

int check_death(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->dead_mutex);
	if (monitor->is_dead = true)
	{
		pthread_mutex_unlock(&monitor->dead_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&monitor->dead_mutex);
	return (0);
}

void	*jcvd_routine(void *arg)
{
	t_philo		*philo;
	t_monitor	*monitor;

	philo = (t_philo *)arg;
	monitor = philo->monitor;
	while (1)
	{
		if (check_death(monitor) == -1)
			break ;
		//bouffe
		//dormir
		//penser
	}
}