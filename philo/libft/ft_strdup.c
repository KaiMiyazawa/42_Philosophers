/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:35:52 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/18 15:16:05 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	size_t	count;
	char	*ptr;

	count = ft_strlen(str);
	if (str == NULL)
		return (0);
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	count = 0;
	if (ptr != NULL)
	{
		while (str[count] != '\0')
		{
			ptr[count] = str[count];
			count++;
		}
		ptr[count] = '\0';
	}
	return (ptr);
}
