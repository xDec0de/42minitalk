/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:04:32 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/22 18:57:00 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "printf/ft_printf.h"
# include <signal.h>
# include <limits.h>

# ifndef SIGNAL_SLEEP
#  define SIGNAL_SLEEP 250
# endif

# define SIGSEND_ERR 1
# define SIGSEND_ERRSTR "\e[0;31mError\e[1;30m: \e[0;31mFailed\
 to send signal, is the PID correct?\e[0m\n"

/**
 * @brief The `unsigned long long` type. It just exists
 * because `unsigned long long` is, in fact, very long.
 */
typedef unsigned long long	t_ulong;

/**
 * @brief The size in bits of the t_ulong type.
 * Used to be calculated with `CHAR_BIT * sizeof(t_ulong)`,
 * but the norm only allows constant defines.
 */
# define ULONG_BIT 64

void	stop(char *err_msg, int exit_code);

void	send_signal(int pid, int signum);

#endif
