/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:25:10 by felipe            #+#    #+#             */
/*   Updated: 2024/06/14 10:48:08 by felipe           ###   ########.fr       */
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

void	get_data_from_input(t_data *data, char **av)
{
	data->num_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1000;
	data->time_to_eat = ft_atol(av[3]) * 1000;
	data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		data->num_of_meals = ft_atol(av[5]);
	else
		data->num_of_meals = -1;
}

void	start_data(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	while (++i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].fork_id = i;
	}
}

void	dessign_forks(t_philo *philo, t_fork *fork,
		int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->num_philos;
	philo->first_fork = fork + ((philo_pos + 1) % philo_nbr);
	philo->sec_fork = fork + philo_pos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = fork + philo_pos;
		philo->sec_fork = fork + ((philo_pos + 1) % philo_nbr);
		/* printf("philo %d first fork %d and second fork %d\n", philo->id,
		philo->first_fork->fork_id, philo->sec_fork->fork_id); */
	}
}


void philho_start(t_data *data)
{
	int	i;
	t_philo	*philo;
	
	i = -1;
	while (++i < data->num_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meals = 0;
		philo->data = data;
		dessign_forks(philo, data->forks, i);
	}
}