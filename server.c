/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/17 13:31:08 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	handle_char(char ch)
{
	static char	*buff = NULL;

	buff = append_ch(buff, ch);
	if (ch != '\0')
		return ;
	ft_printf(buff);
	free(buff);
	buff = NULL;
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
		handle_char(ch);
		if (ch == '\0')
		{
			kill(pid, SIGUSR1);
			pid = 0;
		}
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
