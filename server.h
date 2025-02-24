/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:45:19 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/24 18:58:14 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

typedef struct s_server
{
	int		client_pid;
	char	*msg;
	t_ulong	msg_size;
}				t_server;

# define PID_NOTIFY "\e[0;36mServer started with PID\e[1;30m:\
 \e[1;33m%d\e[0m\n"

# define MALLOC_ERR 1
# define MALLOC_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mMalloc failed,\
 stopping server\e[1;30m.\e[0m\n"

t_server	*get_server(t_server *init);

void		stop_server(int exit_code);

void		reset_client_info(t_server *server);

int			check_pid(int incoming_pid);

#endif
