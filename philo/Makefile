# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 17:27:37 by kvisouth          #+#    #+#              #
#    Updated: 2023/04/27 14:00:07 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c \
	src/notlibft.c \
	src/init_args.c \
	src/init_mutex.c \
	src/init_threads.c \
	src/parse_args.c \
	src/routine_death.c \
	src/routine_eat.c \
	src/routine_forks.c \
	src/routine_sleep.c \
	src/routine_think.c \
	src/routine.c \
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