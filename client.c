/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/24 13:42:46 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void send_char_bit(t_client *client)
{
	static int	last_bit = CHAR_BIT - 1;
	static int	i = 0;

	if (last_bit < 0)
	{
		i++;
		last_bit = CHAR_BIT - 1;
	}
	send_bit(client->srv_pid, client->msg[i] >> last_bit & 1);
	if (last_bit == 0 && client->msg[i] == '\0')
		stop(MSG_SENT, 0);
	last_bit--;
}

int	send_size_bit(t_client *client)
{
	static int		last_bit = ULONG_BIT - 1;

	send_bit(client->srv_pid, client->msg_len >> last_bit & 1);
	last_bit--;
	return (last_bit == -1);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	size_sent = 0;
	t_client	*client;

	client = get_client(NULL);
	if (client->srv_pid != info->si_pid)
		return ;
	(void) context;
	if (signum == SIGUSR1)
	{
		if (!size_sent)
			size_sent = send_size_bit(client);
		else
			send_char_bit(client);
	}
	else
		stop(SRV_BUSY_ERRSTR, SRV_BUSY_ERR);
}

// ./client [int:PID] [char*:message]
int	main(int argc, char **args)
{
	t_client	client;

	client.srv_pid = check_input(argc, args);
	client.msg = args[2];
	client.msg_len = ft_strlen(client.msg);
	get_client(&client);
	init_sighandler(signal_handler);
	send_size_bit(&client);
	while (1)
		;
	return (0);
}
