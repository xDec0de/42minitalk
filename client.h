/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:16:49 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/18 17:44:33 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

# define IN_ERR 1
# define IN_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mInvalid\
 input\e[1;30m.\e[0m\n"
# define PID_ERR 2
# define PID_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mInvalid\
 PID\e[1;30m.\e[0m\n"
# define SIG_SEND_ERR 3
# define SIG_SEND_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mFailed\
 to send signal, is the PID correct?\e[0m\n"
# define SRV_STR_RECEIVED "\e[1;30m[\e[1;33mServer\e[1;30m] \e[0;36m\
String received and printed\e[1;30m.\e[0m\n"
# define SRV_BUSY "\e[1;30m[\e[1;33mServer\e[1;30m] \e[0;31mAnother\
 client is using the server, please wait\e[1;30m.\e[0m\n"

int		client_stop(int ext_code);

int		ft_atoi(const char *str);

t_ulong	ft_strlen(char *str);

#endif
