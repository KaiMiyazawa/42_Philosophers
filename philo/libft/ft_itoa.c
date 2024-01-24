/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:28:45 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/18 15:13:48 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_digit(unsigned long n)
{
	unsigned int	digit;

	digit = 1;
	while (n / 10)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static void	make_char(int size, unsigned long n, char *result)
{
	while (n / 10)
	{
		result[size] = n % 10 + 48;
		size--;
		n /= 10;
	}
	result[size] = n % 10 + 48;
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	int		minus;
	long	n_long;

	n_long = (long)n;
	minus = 0;
	if (n_long < 0)
		size = (get_digit(-n_long) + 2) * sizeof(char);
	else
		size = (get_digit(n_long) + 1) * sizeof(char);
	result = (char *)malloc(size);
	if (!result)
		return (NULL);
	result[--size] = '\0';
	if (n_long < 0)
	{
		n_long = -n_long;
		minus = 1;
	}
	make_char(--size, n_long, result);
	if (minus)
		result[0] = '-';
	return (result);
}
