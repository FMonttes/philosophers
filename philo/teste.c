#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define RED "\033[31m"
#define RST "\033[0m"

typedef struct s_fork {
    pthread_mutex_t fork;
    int fork_id;
} t_fork;

typedef enum e_token {
    FORK,
    EAT,
    SLEEP,
    THINK,
    DIE
} t_token;

typedef struct s_philo {
    int id;
    int meals;
    bool full;
    pthread_t th_id;
    struct s_data *data;
    t_fork *first_fork;
    t_fork *sec_fork;
} t_philo;

typedef struct s_data {
    int nbr_of_philo;
    int num_of_meals;
    bool ths_ready;
    long start_time;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    bool end;
    pthread_mutex_t data_mutex;
    pthread_mutex_t ths_ready_mutex;
    t_fork *forks;
    t_philo *philos;
} t_data;

void *philo_life(void *data);
void get_data_from_input(t_data *data, char **av);
void start_data(t_data *data);
void philho_start(t_data *data);
void dinner_start(t_data *data);
void wait_ths(t_data *data);
void write_status(t_philo *philo, t_token token);

long ft_atol(const char *nptr) {
    long res = 0;
    int sign = 1;

    while ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13))
        nptr++;
    if (*nptr == '-' || *nptr == '+') {
        if (*nptr == '-')
            sign = -1;
        nptr++;
    }
    while (*nptr >= '0' && *nptr <= '9') {
        res *= 10;
        res += *nptr++ - '0';
    }
    return res * sign;
}

void get_data_from_input(t_data *data, char **av) {
    data->nbr_of_philo = ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]);
    data->time_to_eat = ft_atol(av[3]);
    data->time_to_sleep = ft_atol(av[4]);
    if (av[5])
        data->num_of_meals = ft_atol(av[5]);
    else
        data->num_of_meals = -1;
}

void start_data(t_data *data) {
    int i = -1;

    data->end = false;
    data->ths_ready = false;
    pthread_mutex_init(&data->data_mutex, NULL);
    pthread_mutex_init(&data->ths_ready_mutex, NULL);
    data->forks = malloc(sizeof(t_fork) * data->nbr_of_philo);
    data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
    while (++i < data->nbr_of_philo) {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].fork_id = i;
    }
}

void dessign_forks(t_philo *philo, t_fork *fork, int philo_pos) {
    int philo_nbr = philo->data->nbr_of_philo;

    philo->first_fork = fork + ((philo_pos + 1) % philo_nbr);
    philo->sec_fork = fork + philo_pos;
    if (philo->id % 2 == 0) {
        philo->first_fork = fork + philo_pos;
        philo->sec_fork = fork + ((philo_pos + 1) % philo_nbr);
    }
}

void philho_start(t_data *data) {
    int i = -1;
    t_philo *philo;

    while (++i < data->nbr_of_philo) {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->meals = 0;
        philo->full = false;
        philo->data = data;
        dessign_forks(philo, data->forks, i);
    }
}

void dinner_start(t_data *data) {
    printf("Dinner started\n");
    int i = -1;
    struct timeval av;

    if (data->num_of_meals == 0 || data->nbr_of_philo == 1) {
        printf("Returning early from dinner_start\n");
        return;
    }

    while (++i < data->nbr_of_philo) {
        printf("Creating thread %d\n", i);
        pthread_create(&data->philos[i].th_id, NULL, philo_life, &data->philos[i]);
    }
    gettimeofday(&av, NULL);
    data->start_time = (av.tv_sec * 1000) + (av.tv_usec / 1000);

    pthread_mutex_lock(&data->ths_ready_mutex);
    data->ths_ready = true;
    pthread_mutex_unlock(&data->ths_ready_mutex);

    i = -1;
    while (++i < data->nbr_of_philo) {
        printf("Joining thread %d\n", i);
        pthread_join(data->philos[i].th_id, NULL);
    }
}

void wait_ths(t_data *data) {
    while (1) {
        pthread_mutex_lock(&data->ths_ready_mutex);
        if (data->ths_ready) {
            pthread_mutex_unlock(&data->ths_ready_mutex);
            break;
        }
        pthread_mutex_unlock(&data->ths_ready_mutex);
        usleep(1000);  // Avoid busy-waiting
    }
}

void write_status(t_philo *philo, t_token token) {
    struct timeval tv;
    long time;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->data->start_time;
    pthread_mutex_lock(&mutex);
    if (!philo->data->end) {
        if (token == FORK)
            printf("%ld %d has taken a fork\n", time, philo->id);
        else if (token == EAT)
            printf("%ld %d is eating\n", time, philo->id);
        else if (token == SLEEP)
            printf("%ld %d is sleeping\n", time, philo->id);
        else if (token == THINK)
            printf("%ld %d is thinking\n", time, philo->id);
        else if (token == DIE)
            printf("%ld %d died\n", time, philo->id);
    }
    pthread_mutex_unlock(&mutex);
}

static void think(t_philo *philo) {
    write_status(philo, THINK);
}

static void eat(t_philo *philo) {
    pthread_mutex_lock(&philo->first_fork->fork);
    write_status(philo, FORK);
    pthread_mutex_lock(&philo->sec_fork->fork);
    write_status(philo, FORK);
    write_status(philo, EAT);
    usleep(philo->data->time_to_eat * 1000);
    philo->meals++;
    if (philo->data->num_of_meals > 0 && philo->meals == philo->data->num_of_meals)
        philo->full = true;
    pthread_mutex_unlock(&philo->first_fork->fork);
    pthread_mutex_unlock(&philo->sec_fork->fork);
}

void *philo_life(void *data) {
    t_philo *philo = (t_philo *)data;

    wait_ths(philo->data);
    while (1) {
        if (philo->data->end) {
            break;
        }
        eat(philo);
        write_status(philo, SLEEP);
        usleep(philo->data->time_to_sleep * 1000);
        think(philo);
    }
    return NULL;
}

int main(int ac, char **av) {
    t_data data;
    if (ac == 5 || ac == 6) {
        printf("Getting data from input\n");
        get_data_from_input(&data, av);
        printf("Starting data\n");
        start_data(&data);
        printf("Starting philosophers\n");
        philho_start(&data);
        printf("Starting dinner\n");
        dinner_start(&data);
    } else {
        printf(RED "Error: Wrong number of arguments\n" RST);
    }

    // Cleanup
    for (int i = 0; i < data.nbr_of_philo; i++) {
        pthread_mutex_destroy(&data.forks[i].fork);
    }
    pthread_mutex_destroy(&data.data_mutex);
    pthread_mutex_destroy(&data.ths_ready_mutex);
    free(data.forks);
    free(data.philos);

    return 0;
}