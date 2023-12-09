/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:11:34 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/03 09:52:28 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

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
// pthread_mutex_init    //mutex は fork をスレッド固有の変数にしたり、共有変数にしたりする。
// pthread_mutex_destroy
// pthread_mutex_lock,
// pthread_mutex_unlock

static bool	data_init(int ac, char *av[], t_data *d)
{
	d->num_philo = ft_atoi(av[1]);
	d->t_die = ft_atoi(av[2]);
	d->t_eat = ft_atoi(av[3]);
	d->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		d->t_m_eat = ft_atoi(av[5]);
	return (true);
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
		if (av[c1][c2] == '+')
			c2++;
		if (av[c1][c2] >= '0' && av[c1][c2] <= '9')
		{
			c1++;
			continue ;
		}
		else
			return (false);

	}
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc <= 4 || argc >= 7)
		return (1);
	if (check_arg(argv) == false)
		return (1);
	if (data_init(argc, argv, &data) == false)
		return (1);
	printf("===== good case =====\n");
	printf("num_philio\t%d\n", data.num_philo);
	printf("t_die\t\t%d\n", data.t_die);
	printf("t_eat\t\t%d\n", data.t_eat);
	printf("t_sleep\t\t%d\n", data.t_sleep);
	printf("t_m_eat\t\t%d\n", data.t_m_eat);
}
