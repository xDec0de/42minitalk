/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:59:34 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/23 20:37:47 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server *get_server(t_server *init)
{
	static t_server	*server;

	if (init != NULL)
		server = init;
	return (server);
}

void	stop_server(int exit_code)
{
	t_server	*server;

	server = get_server(NULL);
	if (exit_code == MALLOC_ERR)
		ft_printf(MALLOC_ERR_STR);
	if (server->msg != NULL)
		free(server->msg);
	exit(exit_code);
}

void	reset_client_info(t_server *server)
{
	server->client_pid = 0;
	if (server->msg == NULL)
		return ;
	free(server->msg);
	server->msg = NULL;
}

int	check_pid(int incoming_pid)
{
	t_server	*server;

	server = get_server(NULL);
	if (server->client_pid == 0)
	{
		server->client_pid = incoming_pid;
		return (1);
	}
	if (server->client_pid == incoming_pid)
		return (1);
	kill(incoming_pid, SIGUSR2);
	return (0);
}
