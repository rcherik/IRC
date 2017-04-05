/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 16:16:18 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:44:57 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		add_port(t_client *client, char *s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '\n')
			ft_error("bad port.");
		i++;
	}
	client->port = ft_atoi(s);
	if (client->port < 0 || client->port >= 65535)
		ft_error("bad port range.");
}

int			main(int argc, char **argv)
{
	t_client	*client;

	if (argc < 2 || argc > 3)
	{
		ft_putendl("usage: ./client [port [addr]]");
		return (-1);
	}
	client = (t_client *)malloc(sizeof(t_client));
	add_port(client, argv[1]);
	if (argc == 3)
		start_client(client, argv[2]);
	else
		start_client(client, "127.0.0.1");
	return (0);
}
