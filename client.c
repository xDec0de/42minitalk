/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/14 14:58:09 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	client_stop(int ext_code)
{
	if (ext_code == IN_ERR)
		ft_printf(IN_ERR_STR);
	else if (ext_code == PID_ERR)
		ft_printf(PID_ERR_STR);
	else if (ext_code == SIG_SEND_ERR)
		ft_printf(SIG_SEND_ERR_STR);
	exit(ext_code);
}

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
	int	j;

	j = 7;
	while (j >= 0)
	{
		if (ch >> j & 1)
		{
			if (kill(pid, SIGUSR1) != 0)
				client_stop(SIG_SEND_ERR);
		}
		else if (kill(pid, SIGUSR2) != 0)
			client_stop(SIG_SEND_ERR);
		j--;
		usleep(SIGNAL_SLEEP);
	}
	return (1);
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

	i = 0;
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	pid = check_input(argc, args);
	while (args[2][i] != '\0')
		i += send_char(args[2][i], pid);
	send_char('\0', pid);
	return (0);
}
