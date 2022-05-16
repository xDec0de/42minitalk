/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:45:19 by danimart          #+#    #+#             */
/*   Updated: 2022/05/15 22:12:18 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define MAX_CONNECTIONS 1024

typedef struct s_client {
	int	pid;
	int	bits[8];
	int	ended;
}				t_client;

#endif
