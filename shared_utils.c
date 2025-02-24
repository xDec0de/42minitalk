/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:23:51 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/24 14:20:22 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	stop(char *err_msg, int exit_code)
{
	ft_printf(err_msg);
	exit(exit_code);
}

void	send_signal(int pid, int signum)
{
	if (kill(pid, signum) == -1)
		stop(SIGSEND_ERRSTR, SIGSEND_ERR);
}

void	init_sighandler(void (*handler)(int, siginfo_t*, void*))
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}
