/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:16:49 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/22 20:32:34 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

# define IN_ERR 100
# define IN_ERRSTR "\e[0;31mError\e[1;30m: \e[0;31mInvalid\
 input\e[1;30m.\e[0m\n"

# define PID_ERR 101
# define PID_ERRSTR "\e[0;31mError\e[1;30m: \e[0;31mInvalid\
 PID\e[1;30m.\e[0m\n"

# define SRV_BUSY_ERR 102
# define SRV_BUSY_ERRSTR "\e[1;30m[\e[1;33mServer\e[1;30m] \e[0;31mAnother\
 client is using the server, please wait\e[1;30m.\e[0m\n"

# define MSG_SENT "\e[1;30m[\e[1;33mServer\e[1;30m] \e[0;36m\
String received and printed\e[1;30m.\e[0m\n"

int		ft_atoi(const char *str);

t_ulong	ft_strlen(char *str);

void	send_bit(int pid, int bit);

char	*get_msg(char *init);

int	check_input(int argc, char **args);

#endif
