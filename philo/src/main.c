/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:26:44 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/02/20 13:16:15 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_argv(int argc, char **argv)
{
	int	c1;
	int	c2;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (true);
	}
	c1 = 0;
	while (argv[++c1])
	{
		c2 = 0;
		while (argv[c1][c2] == ' ')
			c2++;
		if (argv[c1][c2] < '0' || argv[c1][c2] > '9')
		{
			printf("Error: Invalid argument.\n");
			return (true);
		}
	}
	return (false);
}

bool	destory_data(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->mu_printf);
	while (++i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->mutex_fork[i]);
		pthread_mutex_destroy(&data->philos[i].mu_this_philo);
	}
	free(data->philos);
	free(data->mutex_fork);
	free(data->tid_philo);
	pthread_mutex_destroy(&data->mu_data);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_argv(argc, argv))
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv))
		return (1);
	if (init_philo(&data))
		return (1);
	if (data.num_of_philo == 1)
	{
		data.start_time = get_int_time();
		data.philos[0].limit_time = data.start_time + data.time_to_die;
		if (pthread_create(&data.tid_philo[0], NULL, philo, &data.philos[0]))
			return (printf("Error: pthread_create failed.\n"), 1);
		pthread_detach(data.tid_philo[0]);
		while (data.end_flag == false)
			my_sleep(0);
		return (destory_data(&data), 0);
	}
	if (simulation(&data))
		return (destory_data(&data));
	return (0);
}
