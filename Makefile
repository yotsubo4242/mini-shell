# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 01:50:48 by yuotsubo          #+#    #+#              #
#    Updated: 2024/12/03 22:17:28 by tkitahar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./libft/libft.a
SRCS = ./src/main.c \
		./src/builtin/builtin_exit.c \
		./src/builtin/builtin.c \
		./src/builtin/builtin_export.c \
		./src/builtin/builtin_unset.c \
		./src/builtin/builtin_cd.c \
		./src/builtin/builtin_echo.c \
		./src/builtin/builtin_env.c \
		./src/builtin/builtin_pwd.c \
		./src/destruct/destructor.c \
		./src/env/env.c \
		./src/env/hashmap.c \
		./src/exec/interpret.c \
		./src/exec/pipe.c \
		./src/exec/search_path.c \
		./src/redirect/redirect.c \
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
		./src/expand/remove_quote.c \
		./src/expand/special_parameter.c \
		./src/expand/expand_heardoc.c \
		./src/signal/signal.c \
		./src/signal/reset_signal.c \
		./src/xlib/xcalloc.c \
		./src/xlib/xclose.c \
		./src/xlib/xdup2.c \
		./src/xlib/xmalloc.c \
		./src/xlib/xpipe.c \
		./src/xlib/xstrdup.c \
	 	./src/error/error.c \
	 	./src/error/error_exit.c \
	 	./src/error/syntax_error.c


OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g3 -O0
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
