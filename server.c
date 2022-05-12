/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by danimart          #+#    #+#             */
/*   Updated: 2022/05/12 15:51:06 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int signum)
{
	static int	bit_count = 0;
	static char	ch = 0;

	if (signum == SIGUSR1)
		ch = ch | 128 >> bit_count;
	bit_count++;
	if (bit_count == 8)
	{
		ft_printf("%c", ch);
		bit_count = 0;
		ch = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_printf("Server started with PID: %d.\n", getpid());
	while (1)
		;
	return (0);
}
