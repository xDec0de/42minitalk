/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by danimart          #+#    #+#             */
/*   Updated: 2022/05/16 15:10:21 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_client	get_client(int pid)
{
	static int		last_client_id;
	static t_client	clients[MAX_CONNECTIONS];
	t_client		client;
	int				i;

	i = 0;
	while (i <= last_client_id)
	{
		if (clients[i].pid == pid)
		{
			ft_printf("Client found at id %d! Returning it.\n", i);
			return (clients[i]);
		}
		ft_printf("Client pid doesn't match at id %d\n", i);
		i++;
	}
	ft_printf("No client matched %d, creating a new t_client for it at id %d...\n", pid, last_client_id);
	i = 0;
	client.pid = pid;
	while (i <= 7)
		client.bits[i++] = 2;
	client.ended = 0;
	clients[last_client_id] = client;
	last_client_id++;
	return (client);
}

static char	store_bit(t_client client, int bit)
{
	int	i;

	i = 0;
	ft_printf("\nStoring received bit for client %d:\n", client.pid);
	while (client.bits[i] != 2 && i < 8) {
		ft_printf("i = %d\n", i);
		i++;
	}
	if (i == 7) {
		ft_printf("Bit pool is full! Returning A.\n");
		return ('A');
	} else {
		ft_printf("Bit pool is not full, adding %d.\n", bit);
		client.bits[i] = bit;
	}
	return ('\0');
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	char			ch;

	ft_printf("\n---------------------------\nSIGNAL RECEIVED WITH NUM %d\n---------------------------\n", signum);
	(void) context;
	if (signum == SIGUSR1)
		ch = store_bit(get_client(info->si_pid), 1);
	else
		ch = store_bit(get_client(info->si_pid), 0);
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
