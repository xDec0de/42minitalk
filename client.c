/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by danimart          #+#    #+#             */
/*   Updated: 2022/05/11 20:19:36 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	client_stop(int err)
{
	exit(err);
}

// ./client [int:PID] [char*:message]
int	main(int argc, char **args)
{
	int			pid;

	if (argc != 3)
		client_stop(1);
	pid = get_pid(args[1]);
	if (pid == -1)
		client_stop(2);
	ft_printf("Client started with PID: %d.\n", getpid());
	kill(pid, SIGUSR1);
	return (0);
}
