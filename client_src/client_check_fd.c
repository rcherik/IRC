/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_check_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 16:16:09 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:48:21 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
#include <sys/socket.h>
#include <stdlib.h>

static int	ft_connect(t_client *client, char **tmp, int ret, char *line)
{
	if (ft_tablen(tmp) < 2 || ft_tablen(tmp) > 3)
	{
		ft_putendl("/connect <port> [addr]");
		return (0);
	}
	if (send(client->socket, line, ret, 0) <= 0)
		ft_error("Disconnection.");
	add_port(client, tmp[1]);
	if (ft_tablen(tmp) == 3)
		start_client(client, tmp[2]);
	else
		start_client(client, "127.0.0.1");
	return (1);
}

static void	write_to_serv(t_client *client)
{
	char	line[BUF_SIZE + 1];
	int		ret;
	char	**tmp;

	ft_bzero(line, BUF_SIZE + 1);
	ret = read(0, line, BUF_SIZE);
	tmp = ft_strsplit(line, ' ');
	if (ret > 0 && tmp)
	{
		if (!(strcmp(tmp[0], "/connect")))
			ft_connect(client, tmp, ret, line);
		else
		{
			if (send(client->socket, line, ret, 0) <= 0)
				ft_error("Disconnection.");
		}
	}
}

static void	write_to_client(t_client *client)
{
	char	line[BUF_SIZE + 1];
	int		ret;

	ret = recv(client->socket, line, BUF_SIZE, 0);
	if (ret <= 0)
		ft_error("Disconnection.");
	write(1, line, ret - 1);
}

void		check_fd(t_client *client, int ret)
{
	while (ret > 0)
	{
		if (FD_ISSET(0, &client->fd_client))
			write_to_serv(client);
		if (FD_ISSET(client->socket, &client->fd_client))
			write_to_client(client);
		if (FD_ISSET(0, &client->fd_client)
				|| FD_ISSET(client->socket, &client->fd_client))
			ret--;
	}
}
