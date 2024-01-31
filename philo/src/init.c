/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:46:02 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/01/31 18:07:00 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (error_return1("Error: Invalid argument.", d));
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
		return (error_return1("Error: Invalid argument.", d));
	memset(d->thread, 0, sizeof(pthread_t) * d->num_philo);

	d->philo = (t_philo *)malloc(sizeof(t_philo) * d->num_philo);
	if (!d->philo)
		return (error_return1("Error: Invalid argument.", d));
	memset(d->philo, 0, sizeof(t_philo) * d->num_philo);

	d->mutex_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* d->num_philo);
	if (!d->mutex_forks)
		return (error_return1("Error: Invalid argument.", d));
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
		pthread_mutex_init(&d->philo[i].mutex_philo, NULL);
	}
}

bool	init_all(int ac, char *av[], t_data *d)
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