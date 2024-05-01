/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:40:36 by kmiyazaw          #+#    #+#             */
/*   Updated: 2024/04/26 18:51:10 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_monitor(void *p_data)
{
	t_data	*d;

	d = (t_data *)p_data;
	while (d->end_flag == false)
	{
		pthread_mutex_lock(&(d->mu_data));
		if (d->finished_count >= d->num_of_philo)
			d->end_flag = true;
		pthread_mutex_unlock(&(d->mu_data));
	}
	return ((void *)0);
}

static void	check_eat_count(t_data *d, int i)
{
	if (d->philos[i].eat_count >= d->num_of_must_eat)
	{
		pthread_mutex_lock(&(d->mu_data));
		d->finished_count++;
		pthread_mutex_unlock(&(d->mu_data));
		pthread_mutex_lock(&(d->philos[i].mu_this_philo));
		d->philos[i].eat_count++;
		pthread_mutex_unlock(&(d->philos[i].mu_this_philo));
	}
}

void	*all_monitor(void *p_data)
{
	t_data	*d;
	int		i;

	d = (t_data *)p_data;
	while (d->end_flag == false)
	{
		i = -1;
		while (++i < d->num_of_philo)
		{
			if (get_int_time() > d->philos[i].limit_time
				&& d->philos[i].is_eating == false)
			{
				pthread_mutex_lock(&(d->mu_data));
				d->end_flag = true;
				pthread_mutex_unlock(&(d->mu_data));
				put_msg(&d->philos[i], "died");
			}
			if (d->num_of_must_eat > 0)
				check_eat_count(d, i);
		}
	}
	return ((void *)0);
}
