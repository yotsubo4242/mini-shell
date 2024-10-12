# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 01:50:48 by yuotsubo          #+#    #+#              #
#    Updated: 2024/10/13 01:54:16 by yuotsubo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = ./src/main.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline
$(CC) = cc

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
