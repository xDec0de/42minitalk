/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/18 17:49:58 by daniema3         ###   ########.fr       */
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

int	send_char(char ch, int pid)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (ch >> bit & 1)
		{
			if (kill(pid, SIGUSR1) != 0)
				client_stop(SIG_SEND_ERR);
		}
		else if (kill(pid, SIGUSR2) != 0)
			client_stop(SIG_SEND_ERR);
		bit--;
		usleep(SIGNAL_SLEEP);
	}
	return (1);
}

void	send_size(t_ulong size, int pid)
{
	int	bit;

	bit = sizeof(t_ulong);
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
}

static void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf(SRV_STR_RECEIVED);
	else
		ft_printf(SRV_BUSY);
	exit (0);
}

// ./client [int:PID] [char*:message]
int	main(int argc, char **args)
{
	int		pid;
	int		i;
	char	*text;

	i = 0;
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	pid = check_input(argc, args);
	text = args[2];
	send_size(ft_strlen(text), pid);
	while (text[i] != '\0')
		i += send_char(text[i], pid);
	send_char('\0', pid);
	return (0);
}
