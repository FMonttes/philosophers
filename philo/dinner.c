/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:32:06 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 16:54:48 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, 
	gettime(MILLISECONDS));
	increase_long(&philo->data->data_mutex, 
	&philo->data->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simu_end(philo->data))
		usleep(200);
	return NULL;
}
		

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->number_of_eat == 0)
		return ;
	else if (data->number_of_philosophers == 1)
		pthread_create(&data->philos[0].thread_id, NULL, lone_philo, 
		&data->philos[0]);
	else
	{
		while (++i < data->number_of_philosophers)
		{
			pthread_create(&data->philos[i].thread_id, NULL, philo_life,
				&data->philos[i]);
		}
	}
	pthread_create(&data->monitor, NULL, monitor, data);
	data->start_time = gettime(MILLISECONDS);
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(data->philos[i].thread_id, NULL);
	set_bool(&data->data_mutex, &data->end_simu, true);
	pthread_join(data->monitor, NULL);
}
