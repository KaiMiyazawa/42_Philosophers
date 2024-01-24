/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:11:34 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/01/17 16:07:20 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//   ARGUMENTS

// number_of_philosophers
	// The number of philosophers and also the numberof forks.
// time_to_die
	// If a philosopher didn't start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
// time_to_eat
	// The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
// time_to_sleep
	// The time a philosopher will spend sleeping.
// [number_of_times_each_philosopher_must_eat]
	// If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

//   RULES

// Each philosopher has a number ranging from 1 to number_of_philosophers.

// Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

// Any state change of a philosopher must be formatted as follows:

	//◦ timestamp_in_ms X has taken a fork
	//◦ timestamp_in_ms X is eating
	//◦ timestamp_in_ms X is sleeping
	//◦ timestamp_in_ms X is thinking
	//◦ timestamp_in_ms X died

	// Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.

// A displayed state message should not be mixed up with another message.
// A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
// Again, philosophers should avoid dying!

// Your program must not have any data races.

// memset
// printf
// malloc
// free
// write
// usleep
// gettimeofday
// pthread_create
// pthread_detach
// pthread_join
// pthread_mutex_init    //mutex は フォーク をスレッド固有の変数にしたり、共有変数にしたりする。
// pthread_mutex_destroy
// pthread_mutex_lock,
// pthread_mutex_unlock

#include "../include/philosophers.h"

static bool	init_data(int ac, char *av[], t_data *d)
{
	d->num_philo = ft_atoi(av[1]);
	d->t_die = ft_atoi(av[2]);
	d->t_eat = ft_atoi(av[3]);
	d->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		d->num_m_eat = ft_atoi(av[5]);
	else
		d->num_m_eat = -1;
	if (d->num_philo < 0 || d->t_die < 0 || d->t_eat < 0 || d->t_sleep < 0
		|| (ac == 6 && d->num_m_eat < 0))
		return (OUT);
	pthread_mutex_init(&d->mutex_printf, NULL);
	pthread_mutex_init(&d->mutex_data, NULL);
	d->dead = false;
	d->finished = 0;
	return (SAFE);
}

static bool	init_data_alloc(t_data *d)
{
	d->thread = (pthread_t *)malloc(sizeof(pthread_t) * d->num_philo);
	if (!d->thread)
		return (OUT);
	memset(d->thread, 0, sizeof(pthread_t) * d->num_philo);

	d->philo = (t_philo *)malloc(sizeof(t_philo) * d->num_philo);
	if (!d->philo)
		return (OUT);
	memset(d->philo, 0, sizeof(t_philo) * d->num_philo);

	d->mutex_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* d->num_philo);
	if (!d->mutex_forks)
		return (OUT);
	memset(d->mutex_forks, 0, sizeof(pthread_mutex_t) * d->num_philo);
	return (SAFE);
}

static bool	init_data_fork(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_philo)
		pthread_mutex_init(&d->mutex_forks[i], NULL);
	d->philo[0].mutex_fork_left = d->mutex_forks[0];
	d->philo[0].mutex_fork_right = d->mutex_forks[d->num_philo - 1];
	i = 0;
	while (++i < d->num_philo)
	{
		d->philo[i].mutex_fork_left = d->mutex_forks[i];
		d->philo[i].mutex_fork_right = d->mutex_forks[i - 1];
	}
	return (SAFE);
}

static void	init_data_philo(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_philo)
	{
		d->philo[i].d = d;
		d->philo[i].id = i + 1;
		d->philo[i].t_to_die = d->t_die;
		d->philo[i].eat_count = 0;
		d->philo[i].eating = false;
		//d->philo[i].status = 0;
		pthread_mutex_init(&d->philo[i].mutex_philo, NULL);
	}
}

static bool	init_all(int ac, char *av[], t_data *d)
{
	if (init_data(ac, av, d) == OUT)
		return (OUT);
	if (init_data_alloc(d) == OUT)
		return (OUT);
	if (init_data_fork(d) == OUT)
		return (OUT);
	init_data_philo(d);
	return (SAFE);
}

static bool	check_arg(char *av[])
{
	int	c1;
	int	c2;

	c1 = 1;
	while (av[c1])
	{
		c2 = 0;
		while (av[c1][c2] == ' ' || (av[c1][c2] >= 9 && av[c1][c2] <= 13))
			c2++;
		if (av[c1][c2] >= '0' && av[c1][c2] <= '9' && ++c1)
			continue ;
		else
			return (OUT);
	}
	return (SAFE);
}

void	destroy_free(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_printf);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc != 5 && argc != 6) || check_arg(argv) == OUT)
		return (1);
	if (init_all(argc, argv, &data) == OUT)
		return (1);
	show_data(&data);
	if (game(&data) == OUT)
		return (1);
	destroy_free(&data);
	return (0);
}
