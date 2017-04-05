/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 16:16:24 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:28:55 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	init_client(t_client *client, char *addr)
{
	t_hostent		*hostent;
	t_sockaddr		sin;

	hostent = gethostbyname("localhost");
	if (!hostent)
		ft_error("invalid hostname.");
	client->socket = socket(PF_INET, SOCK_STREAM, 0);
	if ((sin.sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE)
		ft_error("malformed address request.");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(client->port);
	if (connect(client->socket,
				(const struct sockaddr *)&sin, sizeof(sin)) == -1)
		ft_error("server unreachable");
}

static void	speak_with_server(t_client *client)
{
	int		ret;

	while (42)
	{
		ft_putstr("$> ");
		FD_ZERO(&client->fd_client);
		FD_SET(0, &client->fd_client);
		FD_SET(client->socket, &client->fd_client);
		ret = select(client->socket + 1, &client->fd_client, NULL, NULL, NULL);
		check_fd(client, ret);
	}
}

void		start_client(t_client *client, char *addr)
{
	init_client(client, addr);
	ft_putendl("Connected to server");
	speak_with_server(client);
	close(client->socket);
}
