/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:32:06 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 07:46:29 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->number_of_eat == 0)
		return ;
	else if (data->number_of_philosophers == 1)
		;
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
