/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribolzi <pribolzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:49:50 by pribolzi          #+#    #+#             */
/*   Updated: 2025/06/19 18:14:06 by pribolzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_monitor t_monitor;

typedef struct s_philo
{
	int				id;
	int				left;
	int				right;
	long long		last_meal;
	int				nb_meal;
	bool			full_meal;
	pthread_mutex_t full_stomach;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_monitor		*monitor;
}					t_philo;

struct s_monitor
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	bool			is_dead;
	int				finish_eat;
	long long		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t message;
	pthread_t 		checker;
	t_philo			*philo;
};

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_philo(char *nptr);
int		check_and_parse(t_monitor *monitor, int argc, char **argv);
int		free_all(t_monitor *monitor);
void	*jcvd_routine(void *arg);
int 	start_all_thread(t_monitor *monitor);
void	*monitoring(void *arg);
long long get_actual_time(void);

#endif