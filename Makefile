# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 22:05:16 by pszleper          #+#    #+#              #
#    Updated: 2023/01/09 09:49:46 by pszleper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

NAME = philo/philo

SRC_DIR = philo/

SRC = $(addprefix $(SRC_DIR), main.c parsing.c routine.c threads.c utils_1.c \
							  utils_2.c utils_3.c)

OBJ = $(SRC:.c=.o)

HEADER = philo/philo.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) $(HEADER) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f */*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
