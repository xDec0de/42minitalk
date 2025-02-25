/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/25 17:22:33 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_char_bit(t_client *client)
{
	static int	i = -1;

	if (client->last_bit < 0)
	{
		i++;
		client->last_bit = CHAR_BIT - 1;
	}
	send_bit(client->srv_pid, client->msg[i] >> client->last_bit & 1);
	if (client->last_bit == 0 && client->msg[i] == '\0')
		stop(MSG_SENT, 0);
	client->last_bit--;
}

int	send_size_bit(t_client *client)
{
	if (client->last_bit < 0)
		client->last_bit = ULONG_BIT - 1;
	send_bit(client->srv_pid, client->msg_len >> client->last_bit & 1);
	client->last_bit--;
	return (client->last_bit == -1);
}

void	handle_stop(t_client *client, int signum)
{
	if (signum == SIGUSR2)
		stop(USER_INTERRUPT_ERRSTR, USER_INTERRUPT_ERR);
	else
		kill(client->srv_pid, SIGUSR2);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	size_sent = 0;
	static int	stopping = 0;
	t_client	*client;

	(void) context;
	client = get_client(NULL);
	if (signum == SIGINT)
	{
		stopping = 1;
		return ;
	}
	if (client->srv_pid != info->si_pid)
		return ;
	if (stopping)
		handle_stop(client, signum);
	else if (signum == SIGUSR1)
	{
		if (!size_sent)
			size_sent = send_size_bit(client);
		else
			send_char_bit(client);
	}
	else
		stop(SRV_CANCEL_ERRSTR, SRV_CANCEL_ERR);
}

// ./client [int:PID] [char*:message]
int	main(int argc, char **args)
{
	t_client	client;

	client.srv_pid = check_input(argc, args);
	client.msg = args[2];
	client.msg_len = ft_strlen(client.msg);
	client.last_bit = -1;
	get_client(&client);
	init_sighandler(signal_handler);
	send_size_bit(&client);
	while (1)
		;
	return (0);
}
