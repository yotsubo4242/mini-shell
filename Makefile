# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 01:50:48 by yuotsubo          #+#    #+#              #
#    Updated: 2024/11/09 16:58:45 by yuotsubo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./libft/libft.a
SRCS = ./src/main.c \
	   	./src/destruct/destructor.c \
		./src/exec/interpret.c \
		./src/exec/pipe.c \
		./src/exec/redirect.c \
		./src/exec/search_path.c \
		./src/tokenize/blank.c \
		./src/tokenize/operators.c \
		./src/tokenize/tokenize.c \
		./src/tokenize/words.c \
		./src/parse/parse.c \
		./src/parse/pipeline.c \
		./src/parse/redirects.c \
		./src/parse/simple_command.c \
		./src/expand/appendcher.c \
		./src/expand/expand.c \
		./src/expand/expand_variable.c \
		./src/expand/is_variable.c \
		./src/expand/remove_quote.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -lreadline -lft
INCLUDES = -I./include -I./libft
$(CC) = cc

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -L./libft $(OBJS) $(LIBS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT) :
	make -C ./libft

clean :
	make clean -C ./libft
	$(RM) $(OBJS)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
