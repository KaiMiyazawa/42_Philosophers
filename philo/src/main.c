/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:11:34 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/01/31 20:48:58 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//   ARGUMENTS

// number_of_philosophers
	// The number of philosophers and also the numberof forks.
// time_to_die
	// If a philosopher didn't start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
// time_to_eat
	// The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
// time_to_sleep
	// The time a philosopher will spend sleeping.
// [number_of_times_each_philosopher_must_eat]
	// If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

//   RULES

// Each philosopher has a number ranging from 1 to number_of_philosophers.

// Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

// Any state change of a philosopher must be formatted as follows:

	//◦ timestamp_in_ms X has taken a fork
	//◦ timestamp_in_ms X is eating
	//◦ timestamp_in_ms X is sleeping
	//◦ timestamp_in_ms X is thinking
	//◦ timestamp_in_ms X died

	// Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.

// A displayed state message should not be mixed up with another message.
// A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
// Again, philosophers should avoid dying!

// Your program must not have any data races.

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
	//show_data(&data);
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
