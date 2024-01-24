/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:08:58 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/18 15:16:24 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count ;
	char	*result;

	while (c >= 256)
		c -= 256;
	while (c < 0)
		c += 256;
	count = ft_strlen(s);
	s += count;
	while (count >= 0)
	{
		if (*s == c)
		{
			result = (char *)s;
			return (result);
		}
		s--;
		count--;
	}
	return (NULL);
}
