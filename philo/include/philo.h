/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:27:03 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/04/26 18:22:34 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <pthread.h>

# include <stdbool.h>
# include <limits.h>

typedef struct s_philo
{
	atomic_int		id;
	atomic_int		eat_count;
	atomic_bool		is_eating;
	atomic_ullong	limit_time;

	pthread_mutex_t	mu_this_philo;
	pthread_mutex_t	*mu_fork_left;
	pthread_mutex_t	*mu_fork_right;

	//pthread_t		tid_monitor;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	atomic_int		num_of_philo;
	atomic_int		time_to_die;
	atomic_int		time_to_eat;
	atomic_int		time_to_sleep;
	atomic_int		num_of_must_eat;

	uint64_t		start_time;

	pthread_t		tid_eat_monitor;
	pthread_t		tid_all_monitor;
	pthread_t		*tid_philo;

	t_philo			*philos;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mu_printf;

	atomic_int		finished_count;
	atomic_bool		end_flag;
	atomic_bool		dead_flag_for_print;
	pthread_mutex_t	mu_data;
}	t_data;

bool		destory_data(t_data *data);
bool		init_data(t_data *data, int ac, char **av);
bool		init_philo(t_data *data);
bool		simulation(t_data *data);

void		my_sleep(int limit_time);
uint64_t	get_int_time(void);
void		put_msg(t_philo *philo, char *msg);
void		eat(t_philo *philo);
void		*philo(void *p_philo);

int			ft_atoi(const char *str);
bool		destory_data(t_data *data);

void		*all_monitor(void *p_data);

#endif
