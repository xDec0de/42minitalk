/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:16:49 by danimart          #+#    #+#             */
/*   Updated: 2022/05/11 20:38:22 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

# define IN_ERR 1
# define IN_ERR_STR "Error: Invalid input.\n"
# define PID_ERR 2
# define PID_ERR_STR "Error: Invalid PID.\n"

int	ft_atoi(const char *pid_str);

#endif
