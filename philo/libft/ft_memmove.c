/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:11:31 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/18 15:15:32 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t size)
{
	int	count;

	if (!s1 && !s2)
		return (NULL);
	if (s1 > s2)
	{
		count = (int)size - 1;
		while (count >= 0)
		{
			*(char *)(s1 + count) = *(char *)(s2 + count);
			count--;
		}
	}
	else
	{
		count = 0;
		while (count < (int)size)
		{
			*(char *)(s1 + count) = *(char *)(s2 + count);
			count++;
		}
	}
	return (s1);
}
