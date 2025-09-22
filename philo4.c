/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:03 by davmoren          #+#    #+#             */
/*   Updated: 2025/07/09 09:26:38 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	simulation_should_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died || philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

static void	take_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->num_philos;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left_fork]);
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->num_philos]);
}

static void	eat_action(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id]);
		print_status(philo, "has taken a fork");
		precise_usleep(philo->data->time_to_die * 2, philo->data);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_mutex);
	precise_usleep(philo->data->time_to_eat, philo->data);
	release_forks(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		precise_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!simulation_should_end(philo))
	{
		print_status(philo, "is thinking");
		eat_action(philo);
		if (simulation_should_end(philo))
			break ;
		print_status(philo, "is sleeping");
		precise_usleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}
