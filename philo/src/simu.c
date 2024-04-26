/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:14:01 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/04/26 18:44:59 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
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

static bool	join_all_threads(t_data *data)
{
	int	i;

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
	if (pthread_create(&data->tid_all_monitor, NULL, all_monitor, data))
		return (printf("Error: pthread_create failed.\n"), true);
	return (join_all_threads(data));
}
