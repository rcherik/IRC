/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 16:25:47 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:25:50 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_tablen(char **t)
{
	int		i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}
