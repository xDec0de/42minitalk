/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:45:19 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/17 13:11:53 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define PID_NOTIFY "\e[0;36mServer started with PID\e[1;30m:\
 \e[1;33m%d\e[0m\n"

int		check_pid(int pid, int incoming_pid);

char	*append_ch(char *str, char ch);

#endif
