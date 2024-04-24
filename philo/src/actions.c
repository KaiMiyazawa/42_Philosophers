/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:54:12 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/04/24 16:17:10 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_int_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)time.tv_sec * 1000 + (uint64_t)time.tv_usec / 1000
		+ (uint64_t)(time.tv_usec % 1000 >= 500));
}

void	put_msg(t_philo *philo, char *msg)
{
	uint64_t	time;

	pthread_mutex_lock(&(philo->data->mu_printf));
	if (philo->data->dead_flag_for_print == true
		|| (philo->data->end_flag == true && msg[0] != 'd'))
	{
		pthread_mutex_unlock(&(philo->data->mu_printf));
		return ;
	}
	time = get_int_time() - philo->data->start_time;
	printf("%llu %d %s\n", time, philo->id, msg);
	if (msg[0] == 'd')
		philo->data->dead_flag_for_print = true;
	pthread_mutex_unlock(&(philo->data->mu_printf));
}

void	my_sleep(int limit_time)
{
	uint64_t	time;

	time = get_int_time();
	while (get_int_time() < time + limit_time)
		usleep(limit_time / 10);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->mu_fork_right);
		put_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->mu_fork_left);
	}
	else
	{
		pthread_mutex_lock(philo->mu_fork_left);
		put_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->mu_fork_right);
	}
	put_msg(philo, "has taken a fork");
	return ;
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	put_msg(philo, "is eating");
	pthread_mutex_lock(&(philo->mu_this_philo));
	philo->is_eating = true;
	philo->limit_time = get_int_time() + philo->data->time_to_die;
	philo->eat_count++;
	my_sleep(philo->data->time_to_eat);
	philo->is_eating = false;
	pthread_mutex_unlock(&(philo->mu_this_philo));
	pthread_mutex_unlock(philo->mu_fork_left);
	pthread_mutex_unlock(philo->mu_fork_right);
}
