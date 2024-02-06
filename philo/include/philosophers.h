/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:23:35 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/02/06 17:40:06 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdbool.h>
# include <limits.h>

# define FAILED -1
# define SAFE 0
# define OUT 1

typedef struct s_philo
{
	pthread_t			monitor;
	int					id;

	unsigned int		eat_count;
	bool				eating;
	uint64_t			t_to_die;

	pthread_mutex_t		mutex_philo;
	pthread_mutex_t		*mutex_fork_left;
	pthread_mutex_t		*mutex_fork_right;

	struct s_data		*d;
}				t_philo;

typedef struct s_data
{
	int				num_philo;
	uint64_t		t_die;
	int				t_eat;
	int				t_sleep;
	unsigned int	num_m_eat;
	uint64_t		t_start;

	pthread_t		g_monitor;
	pthread_t		*thread;
	t_philo			*philo;
	pthread_mutex_t	*mutex_forks;

	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_data;
	bool			dead;
	unsigned int	finished;
}				t_data;

bool		game(t_data *data);

uint64_t	get_now_time(void);
void		eat(t_philo *philo);
void		put_msg(t_philo *pp, char *str);
void		my_sleep(uint64_t t_sleep);

void		*philo(void *p_philo);

bool		init_all(int ac, char *av[], t_data *d);
bool		error_return1(char *msg, t_data *data);
void		destroy_free(t_data *data);

void		*ft_calloc(size_t size);
int			ft_atoi(const char *nptr);



#endif