/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:34:19 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/18 15:13:59 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			count;
	unsigned char	*dest_char;
	unsigned char	*src_char;

	dest_char = (unsigned char *)dest;
	src_char = (unsigned char *)src;
	count = 0;
	if (!dest && !src)
		return (NULL);
	while (count < n)
	{
		dest_char[count] = src_char[count];
		count++;
	}
	return (dest);
}
