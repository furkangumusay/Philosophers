/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:54:23 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/15 22:54:23 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdbool.h>

static inline bool is_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool is_digit(char c)
{
    return (c >= '0' && c <= '9'); 
}

static const char   *valid_input(const char *str)
{
    const char  *nbr;

    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
        exit_err("Please enter only positive values.\n");
    if (!is_digit(*str))
        exit_err("Please enter only numeric values.\n");
    nbr = str;
    return (nbr);
}

static long     ft_atol(const char *str)
{
    long    nbr;
    int     i;

    nbr = 0;
    i = 0;
    str = valid_input(str);
    while (is_digit(*str))
    {
        nbr = (nbr * 10) + (*str++ - '0');
        i++;
    }
    if (i > 10 || nbr > INT_MAX || nbr == 0)
        exit_err("The number is too big\n");
    return (nbr);
}

int    validate_init(char **argv, t_simulation *sim)
{
    sim->philo_count = ft_atol(argv[1]);
    sim->time_to_die = ft_atol(argv[2]);
    sim->time_to_eat = ft_atol(argv[3]);
    sim->time_to_sleep = ft_atol(argv[4]);
    sim->meals_required = -1;
    if (argv[5])
        sim->meals_required = ft_atol(argv[5]);
    sim->philo_ready = 0;
    sim->is_philo_dead = 0;
    sim->s_start = 0;
    sim->philo = NULL;
    sim->forks_mutex = NULL;
    if (init_mutexes(sim))
        return (1);
    if (init_philosophers(sim))
        return (clean_sim(sim), 1);
    return (0);
}
