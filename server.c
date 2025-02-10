/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/10 17:41:49 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	check_pid(int pid, int incoming_pid)
{
	if (incoming_pid == pid)
		return (0);
	kill(incoming_pid, SIGUSR2);
	return (1);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	pid = 0;
	static int	bit_count = 0;
	static char	ch = 0;

	(void) context;
	if (pid == 0)
		pid = info->si_pid;
	if (check_pid(pid, info->si_pid) == 1)
		return ;
	if (signum == SIGUSR1)
		ch = ch | 128 >> bit_count;
	bit_count++;
	if (bit_count == 8)
	{
		if (ch == '\0')
		{
			kill(pid, SIGUSR1);
			pid = 0;
		}
		else
			write(1, &ch, 1);
		bit_count = 0;
		ch = '\0';
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf(PID_NOTIFY, getpid());
	while (1)
		;
	return (0);
}
