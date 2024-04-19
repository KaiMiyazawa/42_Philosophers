/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:53:52 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/04/19 15:05:43 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_invalid_argument(t_data *data, int ac)
{
	if (data->num_of_philo < 1)
		return (true);
	if (data->time_to_die < 1)
		return (true);
	if (data->time_to_eat < 1)
		return (true);
	if (data->time_to_sleep < 1)
		return (true);
	if (ac == 6 && data->num_of_must_eat < 1)
		return (true);
	return (false);
}

bool	init_data(t_data *data, int ac, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_of_must_eat = ft_atoi(av[5]);
	else
		data->num_of_must_eat = -1;
	if (check_invalid_argument(data, ac))
		return (printf("Error: Invalid argument.\n"), true);
	pthread_mutex_init(&data->mu_printf, NULL);
	pthread_mutex_init(&data->mu_data, NULL);
	data->end_flag = false;
	data->dead_flag_for_print = false;
	data->finished_count = 0;
	return (false);
}

static bool	init_fork(t_data *data)
{
	int	i;

	data->tid_philo = (pthread_t *)malloc(sizeof(pthread_t)
			* data->num_of_philo);
	if (!data->tid_philo)
		return (printf("Error: Malloc failed.\n"), true);
	memset(data->tid_philo, 0, sizeof(pthread_t) * data->num_of_philo);
	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_of_philo);
	if (!data->mutex_fork)
		return (printf("Error: Malloc failed.\n"), true);
	memset(data->mutex_fork, 0, sizeof(pthread_mutex_t) * data->num_of_philo);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_init(&data->mutex_fork[i], NULL);
	i = 0;
	data->philos[0].mu_fork_left = &data->mutex_fork[0];
	data->philos[0].mu_fork_right = &data->mutex_fork[data->num_of_philo - 1];
	while (++i < data->num_of_philo)
	{
		data->philos[i].mu_fork_left = &data->mutex_fork[i];
		data->philos[i].mu_fork_right = &data->mutex_fork[i - 1];
	}
	return (false);
}

bool	init_philo(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philos)
		return (printf("Error: Malloc failed.\n"), true);
	memset(data->philos, 0, sizeof(t_philo) * data->num_of_philo);
	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].is_eating = false;
		data->philos[i].limit_time = data->time_to_die;
		pthread_mutex_init(&data->philos[i].mu_this_philo, NULL);
		data->philos[i].data = data;
	}
	if (init_fork(data))
		return (destory_data(data), true);
	return (false);
}
