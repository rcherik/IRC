/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 14:35:38 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:03:56 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		to_client(t_server *srv, char *s, int co)
{
	t_buf	buf;

	buf = srv->clients[co].buf_write;
	ft_strcat(buf.s, s);
	ft_strcat(buf.s, "\n");
	buf.cur = 0;
	buf.end = ft_strlen(s) + 1;
	srv->clients[co].buf_write = buf;
	return (1);
}

void	add_message_to_client(t_server *srv, char *s, int co)
{
	t_buf	buf;

	buf = srv->clients[co].buf_write;
	ft_strcat(buf.s, s);
	ft_strcat(buf.s, "\n");
	buf.end += ft_strlen(s) + 1;
	srv->clients[co].buf_write = buf;
}

void	add_message(t_server *srv, char *s, int co)
{
	t_buf	buf;

	buf = srv->clients[co].buf_write;
	ft_strcat(buf.s, s);
	buf.end += ft_strlen(s);
	srv->clients[co].buf_write = buf;
}

void	client_write(t_server *srv, int co)
{
	int		ret;
	t_buf	tmp;

	tmp = srv->clients[co].buf_write;
	ret = send(co, tmp.s + tmp.cur, tmp.end, 0);
	tmp.cur += ret;
	if (tmp.cur == tmp.end)
	{
		ft_bzero(tmp.s, tmp.end);
		tmp.cur = 0;
		tmp.end = 0;
	}
	srv->clients[co].buf_write = tmp;
}

void	do_write(t_server *srv, int co)
{
	if (srv->clients[co].type == FD_CLIENT)
		client_write(srv, co);
}
