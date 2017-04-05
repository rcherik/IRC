/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 15:03:51 by rcherik           #+#    #+#             */
/*   Updated: 2015/06/23 16:34:26 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include "libft.h"
# include <sys/select.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <stdio.h>

# define BUF_SIZE 1024

typedef struct				s_client
{
	int						socket;
	int						port;
	fd_set					fd_client;
}							t_client;

typedef struct hostent		t_hostent;
typedef struct sockaddr_in	t_sockaddr;

void						add_port(t_client *client, char *argv);
void						ft_error(char *s);
void						start_client(t_client *client, char *addr);
void						check_fd(t_client *client, int ret);

#endif
