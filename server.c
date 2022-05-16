/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by danimart          #+#    #+#             */
/*   Updated: 2022/05/16 20:30:44 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	bit_array_to_char(int arr[])
{
	int		i;
	char	ch;

	ch = 0;
	i = 0;
	while (i < 8)
	{
		if (arr[i] == 1)
			ch = ch | 128 >> i;
		i++;
	}
	return (ch);
}

t_client	*get_client(int pid)
{
	static int		last_client_id;
	static t_client	clients[MAX_CONNECTIONS];
	t_client		client;
	int				i;

	i = 0;
	while (i < last_client_id)
	{
		if (clients[i].pid == pid)
			return (&clients[i]);
		i++;
	}
	i = 0;
	client.pid = pid;
	while (i <= 7)
		client.bits[i++] = 2;
	client.ended = 0;
	clients[last_client_id] = client;
	last_client_id++;
	return (&clients[last_client_id - 1]);
}

static char	store_bit(t_client *client, int bit)
{
	int		i;
	char	ch;

	i = 0;
	while (i < 8)
	{
		if (client->bits[i] == 2)
			break ;
		i++;
	}
	if (i == 8)
	{
		i = 0;
		ch = bit_array_to_char(client->bits);
		while (i <= 7)
			client->bits[i++] = 2;
		client->bits[0] = bit;
		return (ch);
	}
	else
		client->bits[i] = bit;
	return ('\0');
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	char			ch;
	int				pid;
	t_client		*client;

	(void) context;
	pid = info->si_pid;
	client = get_client(pid);
	if (signum == SIGUSR1)
		ch = store_bit(client, 1);
	else
		ch = store_bit(client, 0);
	if (ch != '\0')
		ft_printf("%c", ch);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server started with PID: %d.\n", getpid());
	while (1)
		;
	return (0);
}
