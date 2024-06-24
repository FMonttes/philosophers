/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:41:02 by felipe            #+#    #+#             */
/*   Updated: 2024/06/24 16:13:44 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void dinner_start(t_data *data)
{
    int     i;
    struct timeval av;

    i = -1;
    if (data->num_limit_meals == 0)
        return ;
    else if (data->nbr_of_philo == 1)
        ;
    {
        while (++i < data->nbr_of_philo)
        {
            pthread_create(&data->philos[i].th_id, NULL, philo_life, 
            &data->philos[i]);
        }
    }
    gettimeofday(&av, NULL);
    data->start_time = (av.tv_sec * 1000) + (av.tv_usec / 1000);
    set_bool(&data->data_mutex, &data->ths_ready, true);
    i = -1;
    while (++i < data->nbr_of_philo)
        pthread_join(data->philos[i].th_id, NULL);
}

void    wait_ths(t_data *data)
{
    while (!get_bool(&data->data_mutex, &data->ths_ready))
        ;
}