/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/22 19:08:32 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	check_input(int argc, char **args)
{
	int	pid;

	if (argc != 3)
		stop(IN_ERRSTR, IN_ERR);
	pid = ft_atoi(args[1]);
	if (pid <= 0)
		stop(PID_ERRSTR, PID_ERR);
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
	send_bit(pid, msg[i] >> last_bit & 1);
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
		send_bit(pid, size >> bit & 1);
		usleep(SIGNAL_SLEEP);
		bit--;
	}
	send_next_bit(pid, msg);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void) context;
	if (signum == SIGUSR1)
		send_next_bit(info->si_pid, NULL);
	else
		stop(SRV_BUSY_ERRSTR, SRV_BUSY_ERR);
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
