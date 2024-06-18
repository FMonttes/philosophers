/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:22:14 by felipe            #+#    #+#             */
/*   Updated: 2024/06/14 10:41:51 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

# define RST  "\033[0m"
# define RED  "\033[31m"
# define GRN  "\033[32m"
# define YEL  "\033[33m"
# define BLU  "\033[34m"
# define MAG  "\033[35m"
# define CYN  "\033[36m"
# define WHT  "\033[37m"

typedef struct  s_data t_data;

typedef enum e_token
{
    FORK,
    EAT,
    SLEEP,
    THINK,
    DIE
}   t_token;

typedef struct s_fork
{
    int fork_id;
    pthread_mutex_t fork;
}   t_fork;

typedef struct s_philo
{
    int     id;
    long    meals;
    pthread_t   *th_id;
    t_fork  *first_fork;
    t_fork  *sec_fork;
    t_data  *data;
}   t_philo;

typedef struct s_data
{
    t_fork *forks;
    t_philo *philos;
    long    nbr_of_philo;
    long    num_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    num_of_meals;
}   t_data;


long    ft_atol(const char *nptr);
void	get_data_from_input(t_data *data, char **av);
void    *philo_life(void *philo);
void    start_data(t_data *data);
void philho_start(t_data *data);