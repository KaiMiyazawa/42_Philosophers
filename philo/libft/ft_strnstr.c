/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:03:25 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/18 15:16:20 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		count1;
	int		count2;
	char	*result;

	count1 = -1;
	if (!big && !len)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[++count1] != '\0' && len > 0)
	{
		count2 = 0;
		while (big[count1 + count2] != '\0'
			&& big[count1 + count2] == little[count2])
			count2++;
		if ((size_t)count2 > len--)
			break ;
		if (little[count2] == '\0')
		{
			result = (char *)big;
			return (result + count1);
		}
	}
	return (NULL);
}
