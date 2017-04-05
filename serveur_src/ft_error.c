/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 14:06:13 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:04:18 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		error_cmd(t_server *srv, char *s, int socket, char **tmp)
{
	to_client(srv, s, socket);
	ft_tabfree(tmp);
	return (1);
}

void	ft_error(char *s)
{
	ft_putendl(s);
	exit(-1);
}
