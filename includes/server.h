/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 13:57:04 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:11:14 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/resource.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <netdb.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

# define ROOM_DEFAULT 0
# define ROOM_FREE 1
# define ROOM_USED 2
# define MAX_USER 50
# define FD_FREE 0
# define FD_SRV 1
# define FD_CLIENT 2
# define BUF_SIZE 1024

typedef struct		s_buf
{
	int				cur;
	int				end;
	char			s[BUF_SIZE + 1];
}					t_buf;

typedef struct		s_room
{
	char			*name;
	char			*passwd;
	int				n_user;
	int				*users;
	int				type;
}					t_room;

typedef struct		s_client
{
	char			*name;
	int				type;
	char			buf_read[BUF_SIZE + 1];
	t_buf			buf_write;
	t_room			*room;
}					t_client;

typedef struct		s_server
{
	int				port;
	int				max_fd;
	int				max;
	int				n_room;
	fd_set			fd_read;
	fd_set			fd_write;
	t_client		*clients;
	t_room			*rooms;
}					t_server;

void				ft_error(char *s);
void				start_server(t_server *srv);
void				init_archive(t_server *srv);
int					do_select(t_server *srv);
void				do_write(t_server *srv, int co);
void				check_fd(t_server *srv, int ret);
void				do_read(t_server *srv, int co);
void				send_to_clients(t_server *srv, int co);
int					commands(t_server *srv, int socket);
int					to_client(t_server *srv, char *s, int co);
void				add_message_to_client(t_server *srv, char *s, int co);
void				add_message(t_server *srv, char *s, int co);
int					ft_create(t_server *srv, int socket, char **tmp);
int					error_cmd(t_server *srv, char *s, int socket, char **tmp);
int					ft_join(t_server *srv, int socket, char **tmp);
int					ft_leave(t_server *srv, int socket, char **tmp);
int					remove_client(t_server *srv, int socket);
void				remove_from_room(t_server *srv, int socket);
void				add_to_room(t_server *srv, int socket);
void				display_nick(t_server *srv, int socket, char **tmp);
int					ft_help(t_server *srv, int socket, char **tmp);
#endif
