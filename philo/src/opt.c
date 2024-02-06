/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:16:39 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/02/06 18:16:53 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

uint64_t	get_now_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		exit(EXIT_FAILURE);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_fork_left);
	pthread_mutex_lock(philo->mutex_fork_right);
	put_msg(philo, "has taken a fork");
	put_msg(philo, "has taken a fork");

	pthread_mutex_lock(&(philo->mutex_philo));
	philo->eating = true;
	philo->t_to_die = get_now_time() + philo->d->t_die;
	put_msg(philo, "is eating");
	philo->eat_count++;
	my_sleep(philo->d->t_eat);
	philo->eating = false;
	pthread_mutex_unlock(&(philo->mutex_philo));

	pthread_mutex_unlock(philo->mutex_fork_left);
	pthread_mutex_unlock(philo->mutex_fork_right);
}

void	my_sleep(uint64_t t_sleep)
{
	uint64_t	start;

	start = get_now_time();
	while ((get_now_time() - start) < t_sleep)
		usleep(t_sleep / 10);
}
