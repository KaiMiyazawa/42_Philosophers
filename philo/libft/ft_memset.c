/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:55 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/18 15:15:55 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	unsigned char	*p;
	size_t			count;

	count = 0;
	p = (unsigned char *)s;
	while (count < size)
	{
		*p++ = (unsigned char)c;
		count++;
	}
	return (s);
}
