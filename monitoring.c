/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:29:14 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/20 19:05:32 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_is_stomach_full(t_monitor *monitor, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < monitor->nb_philo)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].nb_meal >= monitor->nb_must_eat)
			philo[i].full_meal = true;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
}

static bool	fill_all_bellies(t_monitor *monitor, t_philo *philo)
{
	int	i;
	int	all;

	i = 0;
	all = 0;
	while (i < monitor->nb_philo)
	{
		if (philo[i].full_meal == true)
			all++;
		i++;
	}
	if (all == monitor->nb_philo)
		return (true);
	return (false);
}

static bool	check_meal(t_monitor *monitor, t_philo *philo)
{
	if (monitor->nb_must_eat == -1)
		return (false);
	check_is_stomach_full(monitor, philo);
	return (fill_all_bellies(monitor, philo));
}

static bool	check_dead(t_philo *philo, t_monitor *monitor)
{
	long long	current_time;
	int			starved;

	current_time = get_actual_time();
	pthread_mutex_lock(&philo->meal_mutex);
	starved = (current_time - philo->last_meal);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (starved > monitor->time_to_die)
	{
		pthread_mutex_lock(&monitor->dead_mutex);
		monitor->is_dead = true;
		pthread_mutex_unlock(&monitor->dead_mutex);
		pthread_mutex_lock(&monitor->message);
		printf("%lld %d %s\n", get_actual_time() - monitor->start, philo->id,
			"died");
		pthread_mutex_unlock(&monitor->message);
		return (true);
	}
	return (false);
}

void	*monitoring(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	while (1)
	{
		i = 0;
		if (check_meal(monitor, monitor->philo) == true)
		{
			pthread_mutex_lock(&monitor->dead_mutex);
			monitor->is_dead = true;
			pthread_mutex_unlock(&monitor->dead_mutex);
			return (NULL);
		}
		while (i < monitor->nb_philo)
		{
			if (check_dead(&monitor->philo[i], monitor) == true)
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
