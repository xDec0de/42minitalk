/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by danimart          #+#    #+#             */
/*   Updated: 2022/05/11 18:24:17 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	test_handler(int signum, siginfo_t *info, void *context)
{
	context = NULL;
	if (signum == SIGUSR1)
		ft_printf("Received SIGUSR1 from client %d\n", info->si_pid);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = test_handler;
	sigaction(SIGUSR1, &sa, NULL);
	ft_printf("Server started with PID: %d.\n", getpid());
	while (1)
		;
	return (0);
}

/*
void    get_pid(int sig, siginfo_t *info, void *context)
{
    signalPid = info->si_pid;
}

int main(int argc, char **argv)
{
    struct sigaction        sa;

    printf("PID: %d\n", getpid());       //display PID for kill()
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = get_pid;
    sigaction(SIGUSR1, &sa, NULL);
    pause();                           //wait for a signal
    printf("PID of signal sender = %d\n", signalPid);
}
*/