/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:45:19 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/19 18:29:38 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define PID_NOTIFY "\e[0;36mServer started with PID\e[1;30m:\
 \e[1;33m%d\e[0m\n"

# define MALLOC_ERR 1
# define MALLOC_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mMalloc failed,\
 stopping server\e[1;30m.\e[0m\n"

void	stop_server(int exit_code);

int		check_pid(int pid, int incoming_pid);

#endif
