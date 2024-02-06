/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:21:24 by aeryilma          #+#    #+#             */
/*   Updated: 2024/02/05 22:50:04 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_isspace_a(const char *chr, int *index)
{
	*index = 0;
	while ((chr[*index] >= 9 && chr[*index] <= 13) || chr[*index] == ' ')
		(*index)++;
}

static int	ft_isaret(char c, int *index)
{
	int	isaret;

	isaret = 1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			isaret *= -1;
		*index += 1;
	}
	return (isaret);
}

int	ft_atoi(const char *nptr)
{
	int	ret_val;
	int	index;
	int	isaret;

	ret_val = 0;
	if (*nptr == '\0')
		return (0);
	ft_isspace_a(nptr, &index);
	isaret = ft_isaret(nptr[index], &index);
	while (nptr[index] == '0')
		index++;
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		ret_val = (ret_val * 10) + (nptr[index++] - '0');
		if (ret_val <= 0)
		{
			if (isaret == -1)
				return (0);
			return (-1);
		}
	}
	return (ret_val * isaret);
}

void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}
