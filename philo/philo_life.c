/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:34:23 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 07:53:22 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->sec_fork->fork);
	write_status(TAKE_SEC_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILLISECONDS));
	philo->meals_counter++;
	write_status(EATING, philo);
	usleep(philo->data->time_to_eat);
	if (philo->data->number_of_eat > 0
		&& philo->meals_counter == philo->data->number_of_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->sec_fork->fork);
}

void	think(t_philo *philo, bool odd)
{
	long	eat;
	long	sleep;
	long	think;

	if (!odd)
		write_status(SLEEPING, philo);
	if (philo->data->number_of_philosophers % 2 == 0)
		return ;
	eat = philo->data->time_to_eat;
	sleep = philo->data->time_to_sleep;
	think = eat * 2 - sleep;
	if (think < 0)
		think = 0;
	usleep(think * 0.40);
}

void	wait_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->all_threads_ready))
		usleep(50);
}

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILLISECONDS));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	de_philo(philo);
	while (!simu_end(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		usleep(philo->data->time_to_sleep);
		think(philo, false);
	}
	return (NULL);
}
