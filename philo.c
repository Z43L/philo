/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:09:42 by davmoren          #+#    #+#             */
/*   Updated: 2025/07/07 13:12:21 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	is_ok;

	is_ok = check_ok(data, argv);
	if (is_ok == 1)
		return (1);
	if (argc == 6)
		data->meal_goal = ft_atoi(argv[5]);
	else
		data->meal_goal = -1;
	if (data->num_philos == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		return (1);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->start_time = get_time_ms();
	data->someone_died = false;
	data->simulation_end = false;
	return (0);
}

static int	init_single_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = &data->philos[i];
	philo->id = i;
	philo->data = data;
	philo->last_meal = data->start_time;
	philo->meals_eaten = 0;
	if (pthread_mutex_init(&philo->meal_mutex, NULL) != 0)
		return (1);
	if (pthread_create(&philo->thread, NULL, &philosopher_routine, philo) != 0)
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (init_single_philo(data, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
	{
		printf("use good");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Error initializing data\n");
		return (1);
	}
	if (init_philosophers(&data) != 0)
	{
		printf("Error initializing philosophers\n");
		cleanup(&data);
		return (1);
	}
	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL);
	cleanup(&data);
	return (0);
}
