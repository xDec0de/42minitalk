/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:16:49 by danimart          #+#    #+#             */
/*   Updated: 2022/05/14 17:11:57 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

# define IN_ERR 1
# define IN_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mInvalid input\e[1;30m.\e[0m\n"
# define PID_ERR 2
# define PID_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mInvalid PID\e[1;30m.\e[0m\n"
# define SIG_SEND_ERR 3
# define SIG_SEND_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mFailed to send signal,\
 is the PID correct?\e[0m\n"

int	ft_atoi(const char *pid_str);

#endif
