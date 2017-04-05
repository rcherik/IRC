/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 13:55:36 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:10:08 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			main(int argc, char **argv)
{
	t_server		*server;
	int				i;

	i = 0;
	if (argc != 2)
	{
		ft_putendl("Usage: ./server <port>");
		return (1);
	}
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_putendl("Bad port.");
			return (1);
		}
		i++;
	}
	server = malloc(sizeof(t_server));
	server->port = atoi(argv[1]);
	start_server(server);
	return (0);
}
