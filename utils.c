/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:09:52 by davmoren          #+#    #+#             */
/*   Updated: 2025/07/08 19:37:30 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
		if (result > 2147483647)
			return (-1);
	}
	return (result * sign);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	is_simulation_over(t_data *data)
{
	int	should_end;

	pthread_mutex_lock(&data->death_mutex);
	should_end = data->someone_died || data->simulation_end;
	pthread_mutex_unlock(&data->death_mutex);
	return (should_end);
}

void	precise_usleep(long milliseconds, t_data *data)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < milliseconds)
	{
		if (is_simulation_over(data))
			break ;
		usleep(500);
	}
}

int	is_num(char *num)
{
	int	i;

	i = 0;
	while (num[i])
		i++;
	if (i >= 7)
		return (1);
	i = 0;
	while (num[i])
	{
		if (num[i] <= '9' && num[i] >= '0')
			i++;
		else
			return (1);
	}
	return (0);
}
