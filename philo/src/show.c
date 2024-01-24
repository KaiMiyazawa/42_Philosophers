/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:19:32 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/01/18 14:04:35 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	show_time(struct timeval time)
{
	printf("time: %ld.%06d\n", time.tv_sec, time.tv_usec);
}

void	show_data(t_data *data)
{
	printf("===== good case =====\n");
	printf("num_philio\t%d\n", data->num_philo);
	printf("t_die\t\t%llu\n", data->t_die);
	printf("t_eat\t\t%d\n", data->t_eat);
	printf("t_sleep\t\t%d\n", data->t_sleep);
	printf("t_m_eat\t\t%d\n\n", data->num_m_eat);
}
