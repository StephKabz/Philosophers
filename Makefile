# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 11:45:28 by kingstephan       #+#    #+#              #
#    Updated: 2025/10/27 14:08:20 by kingstephan      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I includes
RM = rm -rf
SRCS = src/initialisation/routine.c \
		src/initialisation/init.c \
		src/initialisation/time.c \
		src/initialisation/actions.c \
		src/initialisation/simulations.c \
		src/parsing/parse.c \
		src/utils/utils.c \
		src/main.c

		
OBJS := $(SRCS:%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

obj/%.o: %.c includes/philosophers.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) obj

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re