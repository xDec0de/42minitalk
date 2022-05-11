/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by danimart          #+#    #+#             */
/*   Updated: 2022/05/11 17:33:09 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	test_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("Received SIGUSR1!\n");
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server started with PID: %d.\n", pid);
	signal(SIGUSR1, test_handler);
	while (1)
		;
	return (0);
}
