/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:29:14 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/18 17:41:39 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void check_is_stomach_full(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->nb_philo)
	{
		pthread_mutex_lock(&monitor->philo[i].meal_mutex);
		if (monitor->philo[i].nb_meal == monitor->nb_must_eat)
			monitor->philo[i].full_meal = true;
		pthread_mutex_unlock(&monitor->philo[i].meal_mutex);
		i++;
	}
}

static bool fill_all_bellies(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->nb_philo)
	{
		if (monitor->philo[i].full_meal = true)
			i++;
		else
			break ;
	}
	if (i == monitor->nb_philo)
		return (true);
	return (false);
}

static bool check_meal(t_monitor *monitor)
{
	int	i;

	i = 0;
	if (monitor->nb_must_eat == -1)
		return (false);
	check_is_stomach_full(monitor);
	return (fill_all_bellies(monitor));
}

static bool check_dead(t_philo *philo, t_monitor *monitor)
{
	long long	current_time;
	int 		starved;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->meal_mutex);
	starved = (current_time - philo->last_meal);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (starved > monitor->time_to_die)
	{
		pthtread_mutex_lock(&monitor->dead_mutex);
		monitor->is_dead = true;
		pthtread_mutex_lock(&monitor->dead_mutex);
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
		if (check_meal(monitor))
		{
			pthtread_mutex_lock(&monitor->dead_mutex);
			monitor->is_dead = true;
			pthtread_mutex_lock(&monitor->dead_mutex);
			break ;
		}
		i = 0;
		while (i < monitor->nb_philo)
		{
			if (check_dead(&monitor->philo[i], monitor))
				break ;
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
