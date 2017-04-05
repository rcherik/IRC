/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:40:25 by rcherik           #+#    #+#             */
/*   Updated: 2015/02/10 17:13:07 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	if ((s = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (i < size)
	{
		s[i] = '\0';
		i++;
	}
	s[i] = '\0';
	return (s);
}
