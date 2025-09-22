/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:09:58 by davmoren          #+#    #+#             */
/*   Updated: 2025/07/07 14:29:18 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, const char *status)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died && !philo->data->simulation_end)
	{
		current_time = get_time_ms() - philo->data->start_time;
		printf("%ld %d %s\n", current_time, philo->id + 1, status);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

int	check_ok(t_data *data, char **argv)
{
	if (is_num(argv[1]) != 0 || argv[1][0] == '0')
		return (1);
	if (is_num(argv[2]) != 0 || argv[2][0] == '0')
		return (1);
	if (is_num(argv[3]) != 0 || argv[3][0] == '0')
		return (1);
	if (is_num(argv[4]) != 0 || argv[4][0] == '0')
		return (1);
	if (is_num(argv[5]) != 0 || argv[5][0] == '0')
		return (1);
	data->num_philos = ft_atoi(argv[1]);
	if (data->num_philos <= 0)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die <= 0)
		return (1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat <= 0)
		return (1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep <= 0)
		return (1);
	return (0);
}
