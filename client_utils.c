/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:27:39 by danimart          #+#    #+#             */
/*   Updated: 2025/02/18 17:44:17 by daniema3         ###   ########.fr       */
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
