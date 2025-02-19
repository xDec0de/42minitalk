/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:04:32 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/19 16:09:06 by daniema3         ###   ########.fr       */
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

typedef unsigned long long	t_ulong;
# define ULONG_BIT CHAR_BIT * sizeof(t_ulong)

#endif
