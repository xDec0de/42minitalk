/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/22 18:12:43 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	check_input(int argc, char **args)
{
	int	pid;

	if (argc != 3)
		client_stop(IN_ERR);
	pid = ft_atoi(args[1]);
	if (pid <= 0)
		client_stop(PID_ERR);
	return (pid);
}

static void send_next_bit(int pid, char *buff)
{
	static int	srv_pid = 0;
	static int	last_bit = CHAR_BIT - 1;
	static int	i = 0;
	static char	*msg = NULL;

	if (srv_pid == 0)
	{
		srv_pid = pid;
		msg = buff;
	}
	if (pid != srv_pid)
		return ;
	if (last_bit < 0)
	{
		i++;
		last_bit = CHAR_BIT - 1;
	}
	ft_printf("Sending bit %d, index %d to %d\n", last_bit, i, pid);
	if (msg[i] >> last_bit & 1)
	{
		if (kill(pid, SIGUSR1) != 0)
			client_stop(SIG_SEND_ERR);
	}
	else if (kill(pid, SIGUSR2) != 0)
		client_stop(SIG_SEND_ERR);
	last_bit--;
}

void	send_size(int pid, char *msg)
{
	int		bit;
	t_ulong	size;

	size = ft_strlen(msg);
	bit = ULONG_BIT - 1;
	while (bit >= 0)
	{
		if (size >> bit & 1)
		{
			if (kill(pid, SIGUSR1) != 0)
				client_stop(SIG_SEND_ERR);
		}
		else if (kill(pid, SIGUSR2) != 0)
			client_stop(SIG_SEND_ERR);
		bit--;
		usleep(SIGNAL_SLEEP);
	}
	send_next_bit(pid, msg);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void) context;
	if (signum == SIGUSR1)
		send_next_bit(info->si_pid, NULL);
	else
	{
		ft_printf(SRV_BUSY);
		exit(0);
	}
}

// ./client [int:PID] [char*:message]
int	main(int argc, char **args)
{
	int					pid;
	struct sigaction	sa;

	pid = check_input(argc, args);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_size(pid, args[2]);
	while (1)
		;
	return (0);
}
