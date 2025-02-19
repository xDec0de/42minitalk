/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:59 by daniema3          #+#    #+#             */
/*   Updated: 2025/02/19 16:09:29 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>

static char	*handle_size(int signum)
{
	static t_ulong	size = 0;
	static int		bit_count = 0;
	char			*buff;

	if (signum == SIGUSR1)
		size = size | (1 << (ULONG_BIT - bit_count - 1));
	bit_count++;
	if (bit_count != ULONG_BIT)
		return (NULL);
	printf("Allocating %lld bytes\n", size);
	buff = malloc(size * sizeof(char));
	if (buff == NULL)
		return (NULL); // TODO: Stop server
	return (buff);
}

static int handle_char(int signum, int pid, char *buff)
{
	static int	i = 0;
	static int	bit_count = 0;
	static char	ch = '\0';

	if (signum == SIGUSR1)
		ch = ch | 128 >> bit_count;
	bit_count++;
	if (bit_count == CHAR_BIT)
	{
		buff[i] = ch;
		i++;
		bit_count = 0;
		if (ch == '\0')
		{
			ft_printf(buff);
			free(buff);
			buff = NULL;
			i = 0;
			kill(pid, SIGUSR1);
			return (0);
		}
		ch = '\0';
	}
	return (1);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		pid = 0;
	static char *buff = NULL;

	(void) context;
	if (pid == 0)
		pid = info->si_pid;
	if (check_pid(pid, info->si_pid) == 1)
		return ;
	if (buff == NULL)
		buff = handle_size(signum);
	else if (!handle_char(signum, pid, buff))
		pid = 0;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf(PID_NOTIFY, getpid());
	while (1)
		;
	return (0);
}
