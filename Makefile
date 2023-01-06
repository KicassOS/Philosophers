# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 22:05:16 by pszleper          #+#    #+#              #
#    Updated: 2023/01/06 05:13:44 by pszleper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

NAME = philo/philo

SRC_DIR = philo/

SRC = $(addprefix $(SRC_DIR), main.c parsing.c routine.c threads.c utils_1.c)

OBJ = $(SRC:.o=.c)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
