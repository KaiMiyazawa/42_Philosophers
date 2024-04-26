/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:14:01 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/04/26 18:22:07 by miyazawa.ka      ###   ########.fr       */
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

void	*philo(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	//if (pthread_create(&philo->tid_monitor, NULL, monitor, philo))
	//	return (printf("Error: pthread_create failed.\n"), (void *)0);
	//pthread_detach(philo->tid_monitor);
	while (philo->data->end_flag == false)
	{
		eat(philo);
		if (philo->data->end_flag == true)
			break ;
		put_msg(philo, "is sleeping");
		my_sleep(philo->data->time_to_sleep);
		if (philo->data->end_flag == true)
			break ;
		put_msg(philo, "is thinking");
	}
	return ((void *)0);
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
			//if (get_int_time() > d->philos[i].limit_time)
			if (get_int_time() > d->philos[i].limit_time && d->philos[i].is_eating == false)
			{
				pthread_mutex_lock(&(d->mu_data));
				d->end_flag = true;
				pthread_mutex_unlock(&(d->mu_data));
				put_msg(&d->philos[i], "died");
			}
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
	}
	return ((void *)0);
}

bool	simulation(t_data *data)
{
	int	i;

	if (data->num_of_must_eat > 0
		&& pthread_create(&data->tid_eat_monitor, NULL, eat_monitor, data))
		return (printf("Error: pthread_create failed.\n"), true);
	data->start_time = get_int_time();
	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philos[i].limit_time = data->start_time + data->time_to_die;
		if (pthread_create(&data->tid_philo[i], NULL, philo, &data->philos[i]))
			return (printf("Error: pthread_create failed.\n"), true);
	}
	if(pthread_create(&data->tid_all_monitor, NULL, all_monitor, data))
		return (printf("Error: pthread_create failed.\n"), true);
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->tid_philo[i], NULL))
			return (printf("Error: pthread_join failed.\n"), true);
	}
	if (data->num_of_must_eat > 0
		&& pthread_join(data->tid_eat_monitor, NULL))
		return (printf("Error: pthread_join failed.\n"), true);
	if (pthread_join(data->tid_all_monitor, NULL))
		return (printf("Error: pthread_join failed.\n"), true);
	return (false);
}
