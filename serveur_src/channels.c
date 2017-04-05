/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 15:47:21 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 15:53:06 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	make_room(t_server *srv, int socket, char **tmp)
{
	int		i;

	i = 0;
	while (i < srv->max_fd)
	{
		if (srv->rooms[i].type == ROOM_FREE)
		{
			if (ft_tablen(tmp) == 3)
				srv->rooms[i].passwd = ft_strdup(tmp[2]);
			srv->rooms[i].type = ROOM_USED;
			srv->rooms[i].n_user = 1;
			srv->rooms[i].users[0] = socket;
			srv->rooms[i].name = ft_strdup(tmp[1]);
			srv->clients[socket].room = &(srv->rooms[i]);
			srv->n_room += 1;
			return (1);
		}
		i++;
	}
	ft_tabfree(tmp);
	return (1);
}

int			ft_create(t_server *srv, int socket, char **tmp)
{
	int		i;

	i = 0;
	if (ft_tablen(tmp) > 3 || ft_tablen(tmp) < 2)
		return (error_cmd(srv, "/create <room> [password] \n", socket, tmp));
	while (i < srv->max_fd)
	{
		if (srv->rooms[i].type != ROOM_FREE
				&& !ft_strcmp(srv->rooms[i].name, tmp[1]))
			return (error_cmd(srv, "Rooms already exists\n", socket, tmp));
		i++;
	}
	remove_from_room(srv, socket);
	if (srv->n_room == srv->max_fd)
		return (error_cmd(srv, "Max room reached\n", socket, tmp));
	return (make_room(srv, socket, tmp));
}

static int	join_room(t_server *srv, int socket, char **tmp, int i)
{
	if (srv->rooms[i].n_user == MAX_USER)
		return (error_cmd(srv, "Room is full\n", socket, tmp));
	if (srv->rooms[i].passwd != NULL)
	{
		if (ft_tablen(tmp) != 3 || ft_strcmp(tmp[2], srv->rooms[i].passwd))
			return (error_cmd(srv, "Wrong password\n", socket, tmp));
	}
	remove_from_room(srv, socket);
	srv->clients[socket].room = &(srv->rooms[i]);
	srv->rooms[i].n_user += 1;
	add_to_room(srv, socket);
	return (1);
}

int			ft_join(t_server *srv, int socket, char **tmp)
{
	int		i;

	i = 0;
	if (ft_tablen(tmp) > 3 || ft_tablen(tmp) < 2)
		return (error_cmd(srv, "usage: /join <channel> [pwd]\n", socket, tmp));
	while (i < srv->max_fd)
	{
		if (srv->rooms[i].type == ROOM_USED
				&& !ft_strcmp(srv->rooms[i].name, tmp[1]))
			return (join_room(srv, socket, tmp, i));
		i++;
	}
	return (error_cmd(srv, "Room doesnt exist\n", socket, tmp));
}

int			ft_leave(t_server *srv, int socket, char **tmp)
{
	if (ft_tablen(tmp) != 1)
		return (error_cmd(srv, "usage: /leave\n", socket, tmp));
	if (srv->clients[socket].room->type == ROOM_DEFAULT)
		return (error_cmd(srv, "already in default room\n", socket, tmp));
	return (join_room(srv, socket, tmp, 0));
}
