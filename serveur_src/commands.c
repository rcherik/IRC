/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 14:35:11 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:08:58 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	ft_nick(t_server *srv, int socket, char **tmp)
{
	int		i;

	i = 0;
	if (ft_tablen(tmp) != 2 || ft_strlen(tmp[1]) > 9)
		return (error_cmd(srv, "usage: /nick <nick> 9 max\n", socket, tmp));
	while (i <= srv->max)
	{
		if (srv->clients[i].type == FD_CLIENT
				&& !ft_strcmp(tmp[1], srv->clients[i].name))
			return (error_cmd(srv, "name already exists\n", socket, tmp));
		i++;
	}
	display_nick(srv, socket, tmp);
	ft_strdel(&(srv->clients[socket].name));
	srv->clients[socket].name = ft_strdup(tmp[1]);
	ft_tabfree(tmp);
	return (1);
}

static int	ft_who(t_server *srv, int s, char **tmp)
{
	int		i;

	i = 0;
	if (ft_tablen(tmp) != 1)
		return (error_cmd(srv, "usage: /who\n", s, tmp));
	add_message(srv, "In room ", s);
	add_message(srv, srv->clients[s].room->name, s);
	add_message_to_client(srv, ":", s);
	while (i < MAX_USER)
	{
		if (srv->clients[s].room->users[i])
			add_message_to_client(srv,\
					srv->clients[srv->clients[s].room->users[i]].name, s);
		i++;
	}
	if (i)
		add_message_to_client(srv, "", s);
	ft_tabfree(tmp);
	return (1);
}

static char	*msg_util(t_server *srv, int socket, char **tmp, char *msg)
{
	char	*s;

	s = (char *)malloc(BUF_SIZE);
	ft_strcpy(s, "from ");
	ft_strcat(s, srv->clients[socket].name);
	ft_strcat(s, ": ");
	ft_strcat(s, msg + 2 + ft_strlen(tmp[0]) + ft_strlen(tmp[1]));
	ft_strcat(s, "\n");
	return (s);
}

static int	ft_msg(t_server *srv, int socket, char **tmp, char *msg)
{
	int		i;

	i = 0;
	if (ft_tablen(tmp) < 3)
		return (error_cmd(srv, "usage: /msg <nick> <message>\n", socket, tmp));
	if (!ft_strcmp(tmp[1], srv->clients[socket].name))
		return (error_cmd(srv, "You can't whisper to yourself\n", socket, tmp));
	while (i <= srv->max)
	{
		if (srv->clients[i].type == FD_CLIENT
				&& !ft_strcmp(tmp[1], srv->clients[i].name))
			return (error_cmd(srv, msg_util(srv, socket, tmp, msg), i, tmp));
		i++;
	}
	error_cmd(srv, "no user found with that name\n", socket, tmp);
	return (1);
}

int			commands(t_server *srv, int s)
{
	char		**tmp;

	if (srv->clients[s].buf_read[0] != '/')
		return (0);
	srv->clients[s].buf_read[ft_strlen(srv->clients[s].buf_read) - 1] = 0;
	tmp = ft_strsplit(srv->clients[s].buf_read, ' ');
	if (!ft_strcmp(tmp[0], "/nick"))
		return (ft_nick(srv, s, tmp));
	if (!ft_strcmp(tmp[0], "/who"))
		return (ft_who(srv, s, tmp));
	if (!ft_strcmp(tmp[0], "/msg"))
		return (ft_msg(srv, s, tmp, srv->clients[s].buf_read));
	if (!ft_strcmp(tmp[0], "/create"))
		return (ft_create(srv, s, tmp));
	if (!ft_strcmp(tmp[0], "/join"))
		return (ft_join(srv, s, tmp));
	if (!ft_strcmp(tmp[0], "/leave"))
		return (ft_leave(srv, s, tmp));
	if (!ft_strcmp(tmp[0], "/exit") || !(ft_strcmp(tmp[0], "/connect")))
		return (remove_client(srv, s));
	if (!ft_strcmp(tmp[0], "/help"))
		return (ft_help(srv, s, tmp));
	else
		return (error_cmd(srv, "command not found\n", s, tmp));
	return (0);
}
