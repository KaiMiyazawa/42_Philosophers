/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:23:35 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/02 20:14:14 by miyazawa.ka      ###   ########.fr       */
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

typedef struct s_data
{
	int			num_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			t_m_eat;
}				t_data;

int	ft_atoi(const char *str);

#endif