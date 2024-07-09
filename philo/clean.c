/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:47:38 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 07:58:47 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->philos->philo_mutex);
	free(data->forks);
	free(data->philos);
}

void	de_philo(t_philo *philo)
{
	if (philo->data->number_of_philosophers % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(3e4);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}
