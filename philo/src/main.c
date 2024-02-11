/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:26:44 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/02/11 20:04:57 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_argv(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (true);
	}
	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j] == ' ')
			j++;
		if (argv[i][j] < '0' || argv[i][j] > '9')
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
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_argv(argc, argv))//error inside.
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv))//error inside.
		return (1);
	if (init_philo(&data))//error inside.
		return (1);
	if (data.num_of_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		my_sleep(data.time_to_die);
		printf("0 1 died\n");
		destory_data(&data);
		return (0);
	}
	if (simulation(&data))//error inside.
		return (destory_data(&data));
	return (0);
}
//5 800 200 200
//100 800 200 200
//105 800 200 200
//200 800 200 200