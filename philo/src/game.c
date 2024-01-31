/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:46:56 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/01/31 21:38:20 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	put_msg(t_philo *pp, char *msg)
{
	uint64_t	time_stamp;


	pthread_mutex_lock(&(pp->d->mutex_printf));
	time_stamp = get_now_time() - pp->d->t_start;

	if (ft_strncmp("died", msg, sizeof("died")) == 0 && pp->d->dead == false)
	{
		printf("%llu %d %s\n", time_stamp, pp->id, msg);
		pthread_mutex_lock(&pp->d->mutex_data);
		pp->d->dead = true;
		pthread_mutex_unlock(&pp->d->mutex_data);
	}
	if (!pp->d->dead)
		printf("%llu %d %s\n", time_stamp, pp->id, msg);
	pthread_mutex_unlock(&pp->d->mutex_printf);
}

void	*monitor(void *p_philo)
{
	t_philo		*philo;

	philo = (t_philo *)p_philo;
	while (philo->d->dead != true)
	{
		pthread_mutex_lock(&(philo->mutex_philo));
		if (get_now_time() > philo->t_to_die && philo->eating == false)
			put_msg(philo, "died");
		if (philo->eat_count == philo->d->num_m_eat)
		{
			pthread_mutex_lock(&philo->d->mutex_data);
			philo->d->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->d->mutex_data);
		}
		pthread_mutex_unlock(&(philo->mutex_philo));
	}
	return ((void *)0);
}

void	*philo(void *p_philo)
{
	t_philo		*philo;

	philo = (t_philo *)p_philo;
	if (philo->d->num_philo % 2 == 0)
		my_sleep(philo->d->t_eat / 10);
	if (pthread_create(&philo->monitor, NULL, &monitor, philo) == FAILED)
		exit(error_return1("Failed to create monitor thread.", philo->d));
	while (philo->d->dead != true)
	{
		eat(philo);
		put_msg(philo, "sleeping");
		my_sleep(philo->d->t_sleep);
		put_msg(philo, "thinking");
	}
	if (pthread_join(philo->monitor, NULL) == FAILED)
		exit(error_return1("Failed to join monitor thread.", philo->d));
	return ((void *)0);
}

void	*g_monitor(void *p_data)
{
	t_data	*d;

	d = (t_data *)p_data;
	//pthread_mutex_lock(&d->mutex_printf);
	////printf("data val: %d", (int)(&d->dead));
	//pthread_mutex_unlock(&d->mutex_printf);
	while (d->dead == false)
	{
		pthread_mutex_lock(&(d->philo[0].mutex_philo));
		if (d->finished >= (unsigned int)d->num_philo)
			d->dead = true;
		pthread_mutex_unlock(&(d->philo[0].mutex_philo));
	}
	return ((void *)0);
}

bool	game(t_data *d)
{
	int			i;

	d->t_start = get_now_time();
	if (d->num_m_eat > 0 &&
		pthread_create(&d->g_monitor, NULL, &g_monitor, d) == FAILED)
		exit(error_return1("Failed to create monitor thread.", d));

	i = -1;
	while (++i < d->num_philo)
	{
		if (pthread_create(&d->thread[i], NULL, philo, &d->philo[i]) == FAILED)
			exit(error_return1("Failed to create thread.", d));
		my_sleep(1);
	}
	i = -1;
	while (++i < d->num_philo)
	{
		if (pthread_join(d->thread[i], NULL) == FAILED)
			exit(error_return1("Failed to join thread.", d));
	}
	return (SAFE);
}
