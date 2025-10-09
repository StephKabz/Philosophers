# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 11:45:28 by kingstephan       #+#    #+#              #
#    Updated: 2025/10/10 00:23:58 by kingstephan      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS = src/initialisation/init_prog.c \
		src/initialisation/init_threads.c \
		src/initialisation/init_time.c \
		src/parsing/parse.c \
		src/utils/utils.c \
		src/main.c

		
OBJS := $(SRCS:%.c=obj/%.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) obj
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re