/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:11:34 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/02/06 17:56:26 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	error_return1(char *msg, t_data *data)
{
	printf("%s\n", msg);
	if (data)
		destroy_free(data);
	return (OUT);
}

void	destroy_free(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->mutex_printf);
	pthread_mutex_destroy(&data->mutex_data);
	while (++i < data->num_philo)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		pthread_mutex_destroy(&data->philo[i].mutex_philo);
	}
	free(data->thread);
	free(data->philo);
	free(data->mutex_forks);
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
			return (error_return1("Error: Invalid argument.", NULL));
	}
	return (SAFE);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc != 5 && argc != 6) || check_arg(argv) == OUT)
		return (1);
	if (init_all(argc, argv, &data) == OUT)
		return (1);
	if (data.num_philo == 1)
	{
		data.t_start = get_now_time();
		if (pthread_create(&data.thread[0], NULL,
				&philo, &data.philo[0]) == FAILED)
			return (error_return1("ERROR WHILE CREATING THREADS", &data));
		pthread_detach(data.thread[0]);
		while (data.dead == false)
			my_sleep(0);
		destroy_free(&data);
		return (0);
	}
	if (game(&data) == OUT)
		return (1);
	destroy_free(&data);
	return (0);
}
