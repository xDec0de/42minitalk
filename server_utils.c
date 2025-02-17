/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:59:34 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/17 13:30:07 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	check_pid(int pid, int incoming_pid)
{
	if (incoming_pid == pid)
		return (0);
	kill(incoming_pid, SIGUSR2);
	return (1);
}

char	*copy_str_to_str(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*expand_str(char *str)
{
	int		len;
	char	*expanded;

	len = 0;
	while (str[len] != '\0')
		len++;
	len++;
	expanded = malloc((len) * sizeof(char));
	expanded[len] = '\0';
	len--;
	while (len >= 0)
	{
		expanded[len] = str[len];
		len--;
	}
	return (expanded);
}

char	*append_ch(char *str, char ch)
{
	int	len;

	len = 0;
	if (str == NULL)
	{
		str = malloc(1 * sizeof(char));
		str[0] = ch;
		str[0] = '\0';
		return (str);
	}
	while (str[len] != '\0')
		len++;
	str[len] = ch;
	return (str);
}
