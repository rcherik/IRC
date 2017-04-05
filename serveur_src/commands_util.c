/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 16:01:59 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:02:19 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		display_nick(t_server *srv, int socket, char **tmp)
{
	ft_bzero(srv->clients[socket].buf_read, BUF_SIZE);
	ft_strcat(srv->clients[socket].buf_read, srv->clients[socket].name);
	ft_strcat(srv->clients[socket].buf_read, " changed its name to ");
	ft_strcat(srv->clients[socket].buf_read, tmp[1]);
	ft_strcat(srv->clients[socket].buf_read, "\n");
	send_to_clients(srv, socket);
}

void		remove_from_room(t_server *srv, int socket)
{
	int		u;

	u = 0;
	while (u < MAX_USER)
	{
		if (srv->clients[socket].room->users[u] == socket)
		{
			srv->clients[socket].room->users[u] = 0;
			srv->clients[socket].room->n_user -= 1;
			if (!srv->clients[socket].room->n_user
					&& srv->clients[socket].room->type != ROOM_DEFAULT)
			{
				srv->clients[socket].room->type = ROOM_FREE;
				if (srv->clients[socket].room->passwd)
					ft_strdel(&srv->clients[socket].room->passwd);
			}
		}
		u++;
	}
}

void		add_to_room(t_server *srv, int socket)
{
	int		u;

	u = 0;
	while (u < MAX_USER)
	{
		if (!srv->clients[socket].room->users[u])
		{
			srv->clients[socket].room->users[u] = socket;
			return ;
		}
		u++;
	}
}

int			ft_help(t_server *srv, int socket, char **tmp)
{
	return (error_cmd(srv, "\t- /nick <nick>\n\
	- /create <channel> <password>\n\
	- /join <channel> <password>\n\
	- /leave\n\
	- /msg <nick> <msg>\n\
	- /exit\n\
	- /who\n", socket, tmp));
}
