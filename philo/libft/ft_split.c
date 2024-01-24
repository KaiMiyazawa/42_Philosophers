/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:49:20 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/18 15:16:00 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_unique_strlen(char *str, char charset, int count)
{
	int	length;

	length = 0;
	while (str[count] && !(str[count] == charset))
	{
		count++;
		length++;
	}
	return (length);
}

static int	cou_word(char *str, char c)
{
	int	count;
	int	words_flag;
	int	result;

	count = 0;
	result = 0;
	words_flag = 1;
	while (str[count] != '\0')
	{
		if (str[count] == c)
			words_flag = 1;
		else if (words_flag == 1)
		{
			words_flag = 0;
			result++;
		}
		count++;
	}
	return (result);
}

static char	*make_words(char *str, char charset, int count)
{
	int		size_of_word;
	char	*one_word;
	int		k;

	size_of_word = ft_unique_strlen(str, charset, count);
	one_word = (char *)malloc(sizeof(char) * (size_of_word + 1));
	if (!one_word)
		return (NULL);
	k = 0;
	while (k < size_of_word)
		one_word[k++] = str[count++];
	one_word[k] = '\0';
	return (one_word);
}

static int	do_split(char **resu_vec, const char *s, char c)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (s[count] != '\0')
	{
		while (s[count] != '\0' && s[count] == c)
			count++;
		if (s[count] != '\0')
		{
			resu_vec[count2] = make_words((char *)s, c, count);
			if (!resu_vec[count2++])
			{
				while (--count2 >= 0)
					free(resu_vec[count2]);
				return (1);
			}
		}
		while (s[count] != '\0' && s[count] != c)
			count++;
	}
	resu_vec[count2] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**resu_vec;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = cou_word((char *)s, c);
	resu_vec = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!resu_vec)
		return (NULL);
	if (word_count != 0)
	{
		if (do_split(resu_vec, s, c))
		{
			free(resu_vec);
			return (NULL);
		}
	}
	else
	{
		resu_vec[0] = NULL;
		return (resu_vec);
	}
	return (resu_vec);
}
