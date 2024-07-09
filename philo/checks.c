/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:31:20 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 07:45:24 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	die_time;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECONDS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	die_time = philo->data->time_to_die / 1e3;
	if (elapsed > die_time)
		return (true);
	return (false);
}

bool	all_threads_running(pthread_mutex_t *mutex, long *ths, long philo_nbr)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*ths == philo_nbr)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	increase_long(pthread_mutex_t *mutex, long *var)
{
	pthread_mutex_lock(mutex);
	*var += 1;
	pthread_mutex_unlock(mutex);
}

void	*monitor(void *dat)
{
	int		i;
	t_data	*data;

	data = (t_data *)dat;
	while (!all_threads_running(&data->data_mutex, &data->threads_running_nbr,
			data->number_of_philosophers))
		usleep(50);
	while (!simu_end(data))
	{
		i = -1;
		while (++i < data->number_of_philosophers && !simu_end(data))
		{
			if (philo_died(&data->philos[i]))
			{
				set_bool(&data->data_mutex, &data->end_simu, true);
				write_status(DIED, &data->philos[i]);
			}
		}
	}
	return (NULL);
}
