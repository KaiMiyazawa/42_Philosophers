/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:22:29 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/20 18:00:08 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	del_speace(char *str)
{
	int	count;

	count = 0;
	while (str[count] == ' ' || (str[count] >= 9 && str[count] <= 13))
		count++;
	return (count);
}

static int	del_sign(int count, char *str)
{
	if (str[count] == '-' || str[count] == '+')
		return (1);
	return (0);
}

static int	minus_judge(int count, char *str)
{
	if (str[count] == '-')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		count;
	int		minus_flag;

	num = 0;
	count = del_speace((char *)str);
	minus_flag = minus_judge(count, (char *)str);
	count += del_sign(count, (char *)str);
	while (str[count] >= '0' && str[count] <= '9')
	{
		if (minus_flag == 0 && num > (LONG_MAX - str[count] + '0') / 10)
			return ((int)LONG_MAX);
		if (minus_flag == 1 && num > (LONG_MAX - str[count] + '0') / 10
			&& - num * 10 + str[count] - '0' != LONG_MIN)
			return ((int)LONG_MIN);
		num *= 10;
		num += str[count] - '0';
		count++;
	}
	if (minus_flag == 1)
		num *= -1;
	return (num);
}
