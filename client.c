/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:54:44 by danimart          #+#    #+#             */
/*   Updated: 2022/05/14 17:11:09 by danimart         ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	unsigned long		i;
	unsigned long long	res;
	int					sign;

	i = 0;
	sign = 0;
	res = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = 1;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	if (res > 9223372036854775807)
	{
		if (sign)
			return (0);
		return (-1);
	}
	if (sign)
		return (-res);
	return (res);
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

void	send_signal(int pid, int signal)
{
	if (kill(pid, signal) != 0)
		client_stop(SIG_SEND_ERR);
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
	pid = check_input(argc, args);
	while (args[2][i] != '\0')
	{
		ch = args[2][i];
		j = 7;
		while (j >= 0)
		{
			if (ch >> j & 1)
				send_signal(pid, SIGUSR1);
			else
				send_signal(pid, SIGUSR2);
			j--;
			usleep(300);
		}
		i++;
	}
	return (0);
}
