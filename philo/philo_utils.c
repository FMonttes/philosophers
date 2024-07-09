/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:53:18 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 07:48:15 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res *= 10;
		res += *nptr++ - '0';
	}
	return ((long)(res * sign));
}

void	get_datas(t_data *data, char **av)
{
	data->number_of_philosophers = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1000;
	data->time_to_eat = ft_atol(av[3]) * 1000;
	data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (data->time_to_die < 60000 || data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
	{
		printf(RED "Error: Time must be greater than 60ms\n" RST);
		return ;
	}
	if (av[5])
		data->number_of_eat = ft_atol(av[5]);
	else
		data->number_of_eat = -1;
}

static void	dessign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->number_of_philosophers;
	philo->first_fork = &forks[(pos + 1) % philo_nbr];
	philo->sec_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->sec_fork = &forks[(pos + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->full = false;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		philo->data = data;
		dessign_forks(philo, data->forks, i);
	}
}

void	data_start(t_data *data)
{
	int	i;

	i = -1;
	data->end_simu = false;
	data->all_threads_ready = false;
	data->threads_running_nbr = 0;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->forks = malloc(sizeof(t_fork) * data->number_of_philosophers);
	pthread_mutex_init(&data->data_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].id = i;
	}
	philo_init(data);
}
