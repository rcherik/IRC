/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 14:02:26 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:07:52 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	init_default(t_server *srv)
{
	srv->rooms[0].type = ROOM_DEFAULT;
	srv->rooms[0].name = ft_strdup("default");
	srv->rooms[0].passwd = NULL;
	srv->rooms[0].users = malloc(sizeof(int) * MAX_USER);
	ft_bzero(srv->rooms[0].users, sizeof(int) * MAX_USER);
	srv->rooms[0].n_user = 0;
}

static void init_room(t_server *srv, int i)
{
	srv->rooms[i].type = ROOM_FREE;
	srv->rooms[i].name = NULL;
	srv->rooms[i].passwd = NULL;
	srv->rooms[i].n_user = 0;
	srv->rooms[i].users = malloc(sizeof(int) * MAX_USER);
	ft_bzero(srv->rooms[i].users, sizeof(int) * MAX_USER);
	srv->clients[i].type = FD_FREE;
}

static void	init_server(t_server *srv)
{
	unsigned int		i;
	struct rlimit		r;

	if (getrlimit(RLIMIT_NOFILE, &r) == -1)
		ft_error("getrlimit");
	srv->max_fd = r.rlim_cur;
	srv->n_room = 1;
	srv->clients = (t_client *)malloc(sizeof(t_client) * r.rlim_cur);
	srv->rooms = (t_room *)malloc(sizeof(t_room) * r.rlim_cur);
	if (!srv->clients)
		ft_error("clients malloc error");
	i = 0;
	while (i < r.rlim_cur)
	{
		if (!i)
			init_default(srv);
		else
			init_room(srv, i);
		i++;
	}
}

static void	create_server(t_server *srv)
{
	int							s;
	struct sockaddr_in			sin;
	struct protoent				*pe;

	if (!(pe = (struct protoent *)getprotobyname("tcp")))
		ft_error("error getting tcp protocol.");
	if ((s = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		ft_error("error getting socket.");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(srv->port);
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		ft_error("port already taken.");
	if (listen(s, 100) == -1)
		ft_error("listen failed.");
	srv->clients[s].type = FD_SRV;
	ft_putendl("Server online.");
}

void		start_server(t_server *srv)
{
	int			ret;

	init_server(srv);
	create_server(srv);
	while (42)
	{
		init_archive(srv);
		ret = do_select(srv);
		check_fd(srv, ret);
	}
}
