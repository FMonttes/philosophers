/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:41:17 by felipe            #+#    #+#             */
/*   Updated: 2024/07/09 16:55:24 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define RST "\x1B[0m"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"

typedef struct s_data	t_data;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	JOIN,
	CREATE
}						t_opcode;

typedef enum e_time
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}						t_time;

typedef enum e_status
{
	DIED,
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FIRST_FORK,
	TAKE_SEC_FORK,
}						t_status;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*sec_fork;
	pthread_t			thread_id;
	pthread_mutex_t		philo_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				number_of_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_eat;
	long				start_time;
	long				threads_running_nbr;
	bool				end_simu;
	bool				all_threads_ready;
	pthread_t			monitor;
	t_philo				*philos;
	t_fork				*forks;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		data_mutex;
}						t_data;

void					get_datas(t_data *data, char **av);
void					data_start(t_data *data);
void					print_error(char *error);
void					*safe_malloc(size_t size);
void					safe_mutex(pthread_mutex_t *mutex, t_opcode opcode);
void					safe_thread(pthread_t *thread, t_opcode opcode,
							void *(*func)(void *), void *data);
void					*philo_life(void *philo);
void					dinner_start(t_data *data);
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
bool					get_bool(pthread_mutex_t *mutex, bool *src);
long					get_long(pthread_mutex_t *mutex, long *src);
void					set_long(pthread_mutex_t *mutex, long *dest,
							long value);
long					gettime(t_time time);
void					smart_usleep(long time, t_data *data);
void					smart_sleep(t_data *t, long long time);
void					write_status(t_status status, t_philo *philo);
bool					simu_end(t_data *data);
void					*monitor(void *data);
void					increase_long(pthread_mutex_t *mutex, long *dest);
bool					all_threads_running(pthread_mutex_t *mutex, long *ths,
							long philo_nbr);
void					increase_long(pthread_mutex_t *mutex, long *var);
void					clean(t_data *data);
void					think(t_philo *philo, bool odd);
void					de_philo(t_philo *philo);
void					wait_threads(t_data *data);