/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 14:35:42 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:03:29 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			remove_client(t_server *srv, int socket)
{
	int		i;

	i = 0;
	close(socket);
	srv->clients[socket].type = FD_FREE;
	ft_strdel(&srv->clients[socket].name);
	while (i < MAX_USER)
	{
		if (srv->clients[socket].room->users[i] == socket)
			srv->clients[socket].room->users[i] = 0;
		i++;
	}
	srv->clients[socket].room->n_user--;
	if (!srv->clients[socket].room->n_user
			&& srv->clients[socket].room->type != ROOM_DEFAULT)
	{
		srv->clients[socket].room->type = ROOM_FREE;
		ft_strdel(&(srv->clients[socket].room->name));
	}
	return (1);
}

static void	put_in_room(t_server *srv, int socket)
{
	int		i;

	i = 0;
	srv->clients[socket].room = &(srv->rooms[0]);
	if (srv->rooms[0].n_user == MAX_USER)
	{
		send(socket, "Room is full\n", ft_strlen("Room is full\n"), 0);
		remove_client(srv, socket);
		return ;
	}
	srv->rooms[0].n_user += 1;
	while (srv->rooms[0].users[i] != 0)
		i++;
	srv->rooms[0].users[i] = socket;
}

void		client_read(t_server *srv, int co)
{
	int		ret;

	ret = recv(co, srv->clients[co].buf_read, BUF_SIZE, 0);
	if (ret <= 0)
		remove_client(srv, co);
	else
	{
		ft_putstr(srv->clients[co].buf_read);
		if (!commands(srv, co))
			send_to_clients(srv, co);
		ft_bzero(srv->clients[co].buf_read, ret);
	}
}

void		srv_accept(t_server *srv, int co)
{
	int					socket;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	socket = accept(co, (struct sockaddr *)&csin, &csin_len);
	if (socket == -1)
		ft_error("failed to connect client");
	srv->clients[socket].type = FD_CLIENT;
	srv->clients[socket].name = ft_itoa(socket);
	put_in_room(srv, socket);
}

void		do_read(t_server *srv, int co)
{
	char	buf[BUF_SIZE + 1];

	ft_bzero(buf, BUF_SIZE + 1);
	if (srv->clients[co].type == FD_SRV)
		srv_accept(srv, co);
	else if (srv->clients[co].type == FD_CLIENT)
		client_read(srv, co);
}
