# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 17:27:37 by kvisouth          #+#    #+#              #
#    Updated: 2023/04/06 15:28:01 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c
OBJ = $(SRC:%.c=%.o)
HEADERS = philo.h
NOTLIBFT = notlibft/libnotlibft.a
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS) $(NOTLIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(NOTLIBFT)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NOTLIBFT):
	make -C notlibft

clean:
	@rm -rf $(OBJ)
	@make -C notlibft clean

fclean: clean
	@rm -f $(NAME)
	@make -C notlibft fclean

re: fclean all

.PHONY: all clean fclean re