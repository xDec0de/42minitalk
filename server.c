/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/24 15:58:28 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*handle_size(int signum, t_server *server)
{
	static t_ulong	size = 0;
	static int		bit_count = 0;

	if (signum == SIGUSR1)
		size = size | (1 << (ULONG_BIT - bit_count - 1));
	bit_count++;
	if (bit_count != ULONG_BIT)
	{
		send_signal(server->client_pid, SIGUSR1);
		return (NULL);
	}
	bit_count = 0;
	server->msg = malloc(size * sizeof(char));
	if (server->msg == NULL)
		stop_server(MALLOC_ERR);
	server->msg[size] = '\0';
	while (size > 0)
	{
		size--;
		server->msg[size] = '\0';
	}
	send_signal(server->client_pid, SIGUSR1);
	return (server->msg);
}

static int	handle_char(int signum, t_server *server)
{
	static int	i = 0;
	static int	bit_count = 0;
	static char	ch = '\0';

	if (signum == SIGUSR1)
		ch = ch | 128 >> bit_count;
	bit_count++;
	if (bit_count == CHAR_BIT)
	{
		server->msg[i] = ch;
		i++;
		bit_count = 0;
		if (ch == '\0')
		{
			ft_printf("%s", server->msg);
			i = 0;
			ch = '\0';
			return (1);
		}
		ch = '\0';
	}
	send_signal(server->client_pid, SIGUSR1);
	return (0);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_server	*server;

	(void) context;
	server = get_server(NULL);
	if (signum == SIGINT)
	{
		if (server->client_pid != 0)
			kill(server->client_pid, SIGUSR2);
		reset_client_info(server);
		usleep(10000);
		exit(0);
	}
	if (!check_pid(info->si_pid))
		return ;
	if (server->msg == NULL)
		server->msg = handle_size(signum, server);
	else if (handle_char(signum, server) == 1)
		reset_client_info(server);
}

int	main(void)
{
	t_server	server;

	server.client_pid = 0;
	server.msg = NULL;
	get_server(&server);
	init_sighandler(signal_handler);
	ft_printf(PID_NOTIFY, getpid());
	while (1)
		;
	return (0);
}
