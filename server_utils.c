/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:59:34 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/19 14:15:40 by daniema3         ###   ########.fr       */
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
