/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:12:30 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 07:43:36 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECONDS) - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_mutex);
	if ((TAKE_FIRST_FORK == status || TAKE_SEC_FORK == status)
		&& !simu_end(philo->data))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simu_end(philo->data))
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (THINKING == status && !simu_end(philo->data))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (SLEEPING == status && !simu_end(philo->data))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "%ld %d died\n" RST, elapsed, philo->id);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

long	gettime(t_time time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (SECONDS == time)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (MILLISECONDS == time)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECONDS == time)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		print_error("Invalid time type");
	return (1337);
}

void	print_error(char *error)
{
	printf(RED "Error: %s\n" RST, error);
	exit(1);
}
