/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_clients.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 14:35:33 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:05:02 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		send_to_clients(t_server *srv, int socket)
{
	int		i;

	i = 0;
	while (i < MAX_USER)
	{
		if (srv->clients[socket].room->users[i]
				&& srv->clients[socket].room->users[i] != socket)
			to_client(srv, srv->clients[socket].buf_read,\
					srv->clients[socket].room->users[i]);
		i++;
	}
	ft_bzero(srv->clients[socket].buf_read, BUF_SIZE);
}
