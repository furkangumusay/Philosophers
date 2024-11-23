/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:57:42 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/15 17:57:42 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

// typedef struct s_philosopher
// {
//     int                 id;             // Filozofun kimlik numarası
//     int                 meals_eaten;    // Kaç kez yemek yedi
//     u_int64_t           last_meal_time; // Son yemek yeme zamanı
//     int                 left_fork_id;   // Sol çatalın ID'si
//     int                 right_fork_id;  // Sağ çatalın ID'si
//     pthread_t           thread_id;      // Filozof için thread kimliği
//     struct s_simulation *simulation;    // Simülasyon yapısına referans
// }                   t_philosopher;

// typedef struct s_simulation
// {
//     unsigned int        philosophers_ready; // Hazır olan filozof sayısı
//     unsigned int        philosopher_count;  // Toplam filozof sayısı
//     unsigned int        time_to_die;        // Ölme süresi (ms)
//     unsigned int        time_to_eat;        // Yemek yeme süresi (ms)
//     unsigned int        time_to_sleep;      // Uyuma süresi (ms)
//     int                 meals_required;     // Her filozof için gereken yemek sayısı (-1 ise sınırsız)
//     int                 is_philosopher_dead;// Bir filozofun öldüğünü belirtir
//     u_int64_t           simulation_start;   // Simülasyonun başlangıç zamanı
//     pthread_mutex_t     general_mutex;      // Genel amaçlı bir mutex
//     pthread_mutex_t     *forks_mutex;       // Çatal mutex dizisi
//     pthread_mutex_t     check_mutex;        // Durum kontrolü için mutex
//     pthread_mutex_t     start_mutex;        // Simülasyon başlangıcı için mutex
//     pthread_mutex_t     time_mutex;         // Zaman hesaplamaları için mutex
//     t_philosopher       *philosophers;      // Filozofların dizisi
// }                   t_simulation;

typedef struct       s_philo
{
    int                 id;
    int                 meals_eaten;
    u_int64_t           last_meal_time;
    int                 left_fork;
    int                 right_fork;
    pthread_t           thread_id;
    struct s_sim        *sim;
}                   t_philo;

typedef struct      s_sim
{
    unsigned int        philo_ready;
    unsigned int        philo_count;
    unsigned int        time_to_die;
    unsigned int        time_to_eat;
    unsigned int        time_to_sleep;
    int                 meals_required;
    int                 is_philo_dead;
    u_int64_t           s_start;
    pthread_mutex_t     general_mutex;
    pthread_mutex_t     *forks_mutex;
    pthread_mutex_t     check_mutex;
    pthread_mutex_t     start_mutex;
    pthread_mutex_t     time_mutex;
    t_philo             *philo;
}                   t_sim;

//main.c
int	begin_sim(t_data *data);
void	*monitor_death(void *arg);
void	philo_life(t_philo *ph, t_data *data);
int	check_death(t_philo *philo);

//cleanup.c
int	clean_sim(t_sim *sim);
int	free_mtx(t_sim *sim);
int	init_err(t_sim *sim, int len, int mutex_level);
int	thread_err(t_sim *sim, int len);
void    exit_err(const char *str);

//utils.c
void	ft_usleep(u_int64_t time);
u_int64_t	get_time(void);
void	print_status(t_philo *philo, char *status);

//init_resources.c
int    init_mutexes(t_sim *sim);
int     init_philosophers(t_sim *sim);

//setup_sim.c
int    validate_init(char **argv, t_simulation *sim);

//philo_actions.c
int	philo_eat(t_philo *philo);
int	philo_sleep(t_philo *philo);
int	acquire_forks(t_philo *philo);
int	release_forks(t_philo *philo);

//philo_monitoring.c
int	philo_dead(t_philo *philo);
int	join_threads(t_sim *sim);
int	philo_check(t_philo *philo);
void	*waiting_area(void *arg);


#endif