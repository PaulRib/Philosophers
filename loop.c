/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:36:05 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/20 18:35:11 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_meal(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->nb_meal++;
	philo->last_meal = get_actual_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_wait(monitor->time_to_eat);
}

static void take_fork(t_philo *philo, t_monitor *monitor)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&monitor->forks[philo->right]);
		print_action(monitor, philo, "has taken a fork");
		pthread_mutex_lock(&monitor->forks[philo->left]);
		print_action(monitor, philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&monitor->forks[philo->left]);
		print_action(monitor, philo, "has taken a fork");
		pthread_mutex_lock(&monitor->forks[philo->right]);
		print_action(monitor, philo, "has taken a fork");
	}
	print_action(monitor, philo, "is eating");
	update_meal(philo, monitor);
	pthread_mutex_unlock(&monitor->forks[philo->left]);
	pthread_mutex_unlock(&monitor->forks[philo->right]);
}

static int check_death(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->dead_mutex);
	if (monitor->is_dead == true)
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
			return (NULL);
		take_fork(philo, monitor);
		print_action(monitor, philo, "is sleeping");
		philo_wait(monitor->time_to_sleep);
		print_action(monitor, philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}
