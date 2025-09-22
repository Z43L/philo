/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:10:17 by davmoren          #+#    #+#             */
/*   Updated: 2025/07/08 19:31:27 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		meal_mutex;
	long				last_meal;
	int					meals_eaten;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	long				start_time;
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_goal;
	bool				someone_died;
	bool				simulation_end;
	t_philo				*philos;
}						t_data;

// Funciones utilitarias
int						ft_atoi(const char *str);
long					get_time_ms(void);
void					precise_usleep(long milliseconds, t_data *data);
int						is_num(char *num);
// Funciones principales
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);
int						init_data(t_data *data, int argc, char **argv);
int						init_philosophers(t_data *data);
void					cleanup(t_data *data);
void					print_status(t_philo *philo, const char *status);
int						check_ok(t_data *data, char **argv);
#endif