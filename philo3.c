/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:09:34 by davmoren          #+#    #+#             */
/*   Updated: 2025/07/09 09:03:19 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_death(t_data *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	time_since_last_meal = get_time_ms() - data->philos[i].last_meal;
	if (time_since_last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = true;
			printf("%ld %d died\n", get_time_ms() - data->start_time,
				data->philos[i].id + 1);
		}
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (0);
}

static int	check_meal_goal(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->meal_goal <= 0)
		return (0);
	finished_eating = 0;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten >= data->meal_goal)
			finished_eating++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if (finished_eating == data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_end = true;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		if (check_meal_goal(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
