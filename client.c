/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by danimart          #+#    #+#             */
/*   Updated: 2022/05/12 15:58:15 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	client_stop(int ext_code)
{
	if (ext_code == IN_ERR)
		ft_printf(IN_ERR_STR);
	else if (ext_code == PID_ERR)
		ft_printf(PID_ERR_STR);
	exit(ext_code);
}

// ./client [int:PID] [char*:message]
int	main(int argc, char **args)
{
	int		pid;
	int		i;
	int		j;
	char	ch;

	i = 0;
	j = 0;
	if (argc != 3)
		return (client_stop(IN_ERR));
	pid = ft_atoi(args[1]);
	if (pid == -1)
		return (client_stop(PID_ERR));
	while (args[2][i] != '\0')
	{
		ch = args[2][i];
		j = 7;
		ft_printf("Client send: ");
		while (j >= 0)
		{
			if (ch >> j & 1) {
				ft_printf("1");
				kill(pid, SIGUSR1);
			} else {
				ft_printf("0");
				kill(pid, SIGUSR2);
			}
			j--;
			usleep(10);
		}
		ft_printf("\n");
		i++;
	}
	return (0);
}
