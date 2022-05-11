# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danimart <danimart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 10:19:42 by danimart          #+#    #+#              #
#    Updated: 2022/05/11 20:20:19 by danimart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minitalk
SNAME=server
CNAME=client
CC=gcc

CFLAGS=-Wall -Werror -Wextra

SANITIZE=-g3 -fsanitize=address

COMC_FILES=printf/ft_printf.c printf/write_num.c printf/write_txt.c
COMO_FILES=$(COMC_FILES:.c=.o)

SC_FILES=server.c
SO_FILES=$(SC_FILES:.c=.o)

CC_FILES=client.c input_utils.c
CO_FILES=$(CC_FILES:.c=.o)

all: $(NAME)
headermk:
	@printf "\n\e[1;31m> \e[1;36mMaking \e[1;34m$(NAME)\e[1;36m...\
	\n\n\e[0;35mCommands\e[1;30m:\n"
$(NAME): headermk $(SO_FILES) $(CO_FILES) $(COMO_FILES)
	@printf "\n\e[0;33m-\e[1;32m "
	$(CC)$(C_FLAGS) $(COMO_FILES) $(SO_FILES) -o $(SNAME)
	@printf "\e[0;33m-\e[1;32m "
	$(CC)$(C_FLAGS) $(COMO_FILES) $(CO_FILES) -o $(CNAME)
	@printf "\n\033[0m"
clean:
	@printf "\n\e[1;31m> \e[1;36mRemoving \e[1;34m$(NAME)\e[1;36m's objects...\
	\e[1;30m\n\n"
	@printf "\e[0;33m-\e[1;32m "
	rm -rf $(COMO_FILES) $(SO_FILES) $(CO_FILES)
	@printf "\n\033[0m"
fclean:
	@printf "\n\e[1;31m> \e[1;36mRemoving \e[1;34m$(NAME)\e[1;36m...\
	\e[1;30m\n\n"
	@printf "\e[0;33m-\e[1;32m "
	rm -rf $(SNAME) $(CNAME) $(COMO_FILES) $(SO_FILES) $(CO_FILES)
	@printf "\n\033[0m"
sanitize: headermk $(COMO_FILES) $(SO_FILES) $(CO_FILES)
	@printf "\n\e[1;31m- \e[0;33mSanitize enabled\n\e[0;33m-\e[1;32m "
	$(CC)$(C_FLAGS) $(COMO_FILES) $(SO_FILES) -o $(SNAME) $(SANITIZE)
	@printf "\e[0;33m-\e[1;32m "
	$(CC)$(C_FLAGS) $(COMO_FILES) $(CO_FILES) -o $(CNAME) $(SANITIZE)
	@printf "\n\033[0m"
re: fclean $(NAME)
.PHONY: all clean fclean re