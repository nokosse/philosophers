# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 17:27:37 by kvisouth          #+#    #+#              #
#    Updated: 2023/05/03 16:49:08 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c \
	src/init.c \
	src/notlibft.c \
	src/parse.c \
	src/routine.c \
	src/threads.c \
	src/utils.c \
	
OBJ = $(addprefix obj/, $(SRC:.c=.o))
HEADERS = philo.h
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

obj/%.o: %.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re