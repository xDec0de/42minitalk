/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/22 20:35:18 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void send_char_bit(int pid)
{
	static int	srv_pid = 0;
	static int	last_bit = CHAR_BIT - 1;
	static int	i = 0;

	if (srv_pid == 0)
		srv_pid = pid;
	if (pid != srv_pid)
		return ;
	if (last_bit < 0)
	{
		i++;
		last_bit = CHAR_BIT - 1;
	}
	send_bit(pid, get_msg(NULL)[i] >> last_bit & 1);
	if (last_bit == 0 && get_msg(NULL)[i] == '\0')
		stop(MSG_SENT, 0);
	last_bit--;
}

int	send_size_bit(int pid)
{
	static int		srv_pid = 0;
	static int		last_bit = ULONG_BIT - 1;
	static t_ulong	size = 0;

	if (srv_pid == 0)
	{
		srv_pid = pid;
		size = ft_strlen(get_msg(NULL));
	}
	if (pid != srv_pid)
		return (0);
	send_bit(pid, size >> last_bit & 1);
	last_bit--;
	return (last_bit == -1);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int size_sent = 0;
	
	(void) context;
	if (signum == SIGUSR1)
	{
		if (!size_sent)
			size_sent = send_size_bit(info->si_pid);
		else
			send_char_bit(info->si_pid);
	}
	else
		stop(SRV_BUSY_ERRSTR, SRV_BUSY_ERR);
}

// ./client [int:PID] [char*:message]
int	main(int argc, char **args)
{
	int					pid;
	struct sigaction	sa;

	pid = check_input(argc, args);
	get_msg(args[2]);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_size_bit(pid);
	while (1)
		;
	return (0);
}
