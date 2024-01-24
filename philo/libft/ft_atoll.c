/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:11:11 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/20 18:11:24 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	del_speace(char *str)
{
	int	count;

	count = 0;
	while (str[count] == ' ' || (str[count] >= 9 && str[count] <= 13))
		count++;
	return (count);
}

static int	minus_judge(int count, char *str)
{
	if (str[count] == '-')
		return (1);
	return (0);
}

long long	ft_atoll(const char *str)
{
	long long	num;
	int			count;
	int			minus_flag;

	num = 0;
	count = del_speace((char *)str);
	minus_flag = minus_judge(count, (char *)str);
	count += minus_flag;
	while (str[count] >= '0' && str[count] <= '9')
	{
		if (minus_flag == 0 && num > (LLONG_MAX - str[count] + '0') / 10)
			return ((long long)LLONG_MAX);
		if (minus_flag == 1 && num > (LLONG_MAX - str[count] + '0') / 10
			&& - num * 10 + str[count] - '0' != LLONG_MIN)
			return ((long long)LLONG_MIN);
		num *= 10;
		num += str[count] - '0';
		count++;
	}
	if (minus_flag == 1)
		num *= -1;
	return (num);
}
