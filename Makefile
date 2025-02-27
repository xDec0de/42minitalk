# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 10:19:42 by daniema3          #+#    #+#              #
#    Updated: 2025/02/22 20:37:00 by daniema3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
SNAME = server
CNAME = client

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

PRINTFC_FILES = printf/ft_printf.c printf/write_num.c printf/write_txt.c
PRINTFO_FILES = $(PRINTFC_FILES:.c=.o)

SC_FILES = shared_utils.c server.c server_utils.c
SO_FILES = $(SC_FILES:.c=.o)

CC_FILES = shared_utils.c client.c client_utils.c
CO_FILES = $(CC_FILES:.c=.o)

all: $(NAME)

$(NAME): client server

client: $(PRINTFO_FILES) $(CO_FILES)
	$(CC) $(CFLAGS) $(PRINTFO_FILES) $(CO_FILES) -o $(CNAME)

server: $(PRINTFO_FILES) $(SO_FILES)
	$(CC) $(CFLAGS) $(PRINTFO_FILES) $(SO_FILES) -o $(SNAME)

clean:
	rm -rf $(PRINTFO_FILES) $(SO_FILES) $(CO_FILES)

fclean: clean
	rm -rf $(SNAME) $(CNAME)

re: fclean $(NAME)

.PHONY: all clean fclean re