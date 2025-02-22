/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:27:39 by danimart          #+#    #+#             */
/*   Updated: 2025/02/22 20:32:06 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
	if (res > __LONG_MAX__)
	{
		if (sign)
			return (0);
		return (-1);
	}
	if (sign)
		return (-res);
	return (res);
}

t_ulong	ft_strlen(char *str)
{
	t_ulong	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	send_bit(int pid, int bit)
{
	if (bit)
		send_signal(pid, SIGUSR1);
	else
		send_signal(pid, SIGUSR2);
}

char *get_msg(char *init)
{
	static char *msg;

	if (init != NULL)
		msg = init;
	return (msg);
}

int	check_input(int argc, char **args)
{
	int	pid;

	if (argc != 3)
		stop(IN_ERRSTR, IN_ERR);
	pid = ft_atoi(args[1]);
	if (pid <= 0)
		stop(PID_ERRSTR, PID_ERR);
	return (pid);
}
