/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:40:35 by rcherik           #+#    #+#             */
/*   Updated: 2015/01/20 15:40:56 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	if (c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim(char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i])
	{
		j = i;
		while (s[j + 1])
			j++;
		while (j > 0 && ft_isspace(s[j]))
			j--;
		return (ft_strsub(s, i, j - i + 1));
	}
	return (ft_strsub(s, 0, 0));
}
