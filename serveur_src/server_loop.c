/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 14:22:29 by rcherik           #+#    #+#             */
/*   Updated: 2015/02/20 15:56:58 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		check_fd(t_server *srv, int ret)
{
	int			i;

	i = 0;
	while ((i < srv->max_fd) && (ret > 0))
	{
		if (FD_ISSET(i, &srv->fd_read))
			do_read(srv, i);
		if (FD_ISSET(i, &srv->fd_write))
			do_write(srv, i);
		if (FD_ISSET(i, &srv->fd_read) || FD_ISSET(i, &srv->fd_read))
			ret--;
		i++;
	}
}

int			do_select(t_server *srv)
{
	return (select(srv->max + 1, &srv->fd_read, &srv->fd_write, NULL, NULL));
}

void		init_archive(t_server *srv)
{
	int		i;

	i = 0;
	srv->max = 0;
	FD_ZERO(&srv->fd_read);
	FD_ZERO(&srv->fd_write);
	while (i < srv->max_fd)
	{
		if (srv->clients[i].type != FD_FREE)
		{
			FD_SET(i, &srv->fd_read);
			if (ft_strlen(srv->clients[i].buf_write.s) > 0)
				FD_SET(i, &srv->fd_write);
			srv->max = (srv->max > i) ? srv->max : i;
		}
		i++;
	}
}
