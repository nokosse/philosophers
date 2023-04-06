# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 17:27:37 by kvisouth          #+#    #+#              #
#    Updated: 2023/04/06 15:11:52 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c

OBJS = $(SRCS:src/%.c=obj/%.o)
HEADERS = philo.h
NOTLIBFT = notlibft/libnotlibft.a
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(NOTLIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(NOTLIBFT)

obj/%.o: src/%.c $(HEADERS)
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/main.o: main.c $(HEADERS)
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(NOTLIBFT):
	make -C notlibft

clean:
	@rm -rf obj
	@make -C notlibft clean

fclean: clean
	@rm -f $(NAME)
	@make -C notlibft fclean

re: fclean all