/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:19:40 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/18 17:24:41 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_value(t_monitor *monitor, int argc)
{
	if (monitor->nb_philo == -1)
		return (-1);
	if (monitor->time_to_die == -1)
		return (-1);
	if (monitor->time_to_eat == -1)
		return (-1);
	if (monitor->time_to_sleep == -1)
		return (-1);
	if (argc == 6)
		if (monitor->nb_must_eat == -1)
			return (-1);
	return (0);
}

static int alloc_all(t_monitor *monitor)
{
	monitor->forks = malloc(sizeof(pthread_mutex_t) * monitor->nb_philo);
	if (!monitor->forks)
		return (-1);
	monitor->philo = malloc(sizeof(t_philo) * monitor->nb_philo);
	if (!monitor->philo)
		return (-1);
	memset(monitor->philo, 0, sizeof(t_philo));
	return (0);
}

static int	init_all(t_monitor *monitor)
{
	int	i;

	i = 0;
	if (alloc_all(monitor) == -1)
		return (-1);
	while (i < monitor->nb_philo)
	{
		memset(&monitor->philo[i], 0, sizeof(t_philo));
		monitor->philo[i].id = i + 1;
		monitor->philo[i].left = i;
		monitor->philo[i].right = (i + 1) % monitor->nb_philo;
		monitor->philo[i].monitor = monitor;
		pthread_mutex_init(&monitor->forks[i], NULL);
		pthread_mutex_init(&monitor->philo->meal_mutex, NULL);
		pthread_mutex_init(&monitor->philo->full_stomach, NULL);
		i++;
	}
	pthread_mutex_init(&monitor->dead_mutex, NULL);
	return (0);
}

int	check_and_parse(t_monitor *monitor, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (-1);
	monitor->nb_philo = ft_atoi_philo(argv[1]);
	monitor->time_to_die = ft_atoi_philo(argv[2]);
	monitor->time_to_eat = ft_atoi_philo(argv[3]);
	monitor->time_to_sleep = ft_atoi_philo(argv[4]);
	if (argc == 6)
		monitor->nb_must_eat = ft_atoi_philo(argv[5]);
	else
		monitor->nb_must_eat = -1;
	if (check_all_value(monitor, argc) == -1)
		return (-1);
	if (init_all(monitor) == -1)
		return (-1);
	return (0);
}
