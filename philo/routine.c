/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:12:00 by felipe            #+#    #+#             */
/*   Updated: 2024/06/24 16:12:28 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void eat(t_philo *philo)
{
   struct timeval tv;
   long time;

   pthread_mutex_lock(&philo->first_fork->fork);
   write_status(philo, FORK);
   pthread_mutex_lock(&philo->sec_fork->fork);
   write_status(philo, FORK);
   gettimeofday(&tv, NULL);
   time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->data->start_time;
   set_long(&philo->philo_mutex, &philo->last_meal, time);
   philo->meals++;
   write_status(philo, EAT);
   usleep(philo->data->time_to_eat);
   if (philo->data->num_limit_meals > 0 
   && philo->meals == philo->data->num_limit_meals)
      set_bool(&philo->philo_mutex, &philo->full, true);
   pthread_mutex_unlock(&philo->first_fork->fork);
   pthread_mutex_unlock(&philo->sec_fork->fork);
}

void write_status(t_philo *philo, t_token token) 
{

   struct timeval tv;
    long time;
    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->data->start_time;

   if (!philo->full)
      return ;
   pthread_mutex_lock(&philo->data->write_lock);
      if (token == FORK && !simu_end(philo->data))
         printf("%ld %d has taken a fork\n", time, philo->id);
      else if (token == EAT && !simu_end(philo->data))
         printf("%ld %d is eating\n", time, philo->id);
      else if (token == SLEEP && !simu_end(philo->data))
         printf("%ld %d is sleeping\n", time, philo->id);
      else if (token == THINK && !simu_end(philo->data))
         printf("%ld %d is thinking\n", time, philo->id);
      else if (token == DIE && !simu_end(philo->data))
         printf("%ld %d died\n", time, philo->id);
   pthread_mutex_unlock(&philo->data->write_lock);
}


static void think(t_philo *philo)
{
   write_status(philo, THINK);
}


void    *philo_life(void *data)
{
   t_philo  *philo;

   philo = (t_philo *)data;
   wait_ths(philo->data);
   while (!simu_end(philo->data))
   {
      if (philo->full)
         break ;
       eat(philo);
       write_status(philo, SLEEP);
       usleep(philo->data->time_to_sleep);
       think(philo);
   }
}