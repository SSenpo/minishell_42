# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmago <mmago@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/30 22:41:33 by mmago             #+#    #+#              #
#    Updated: 2022/08/12 20:24:10 by mmago            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_PATH = ./includes/libft/
LIB_NAME = ./includes/libft/libft.a

CC = gcc
# gcc -fsanitize=thread флаг для теста потока
CFLAGS = -Wall -Wextra -Werror
RFLAGS = -lreadline -ltermcap -g -L/Users/mmago/.brew/Cellar/readline/8.1.2/lib/ -I/Users/mmago/.brew/Cellar/readline/8.1.2/include
RM = rm -f

FILES = src/main.c src/envp_parser.c src/built_comand.c src/pars_str/check_dollar_one.c src/pars_str/check_dollar_two.c \
		src/unset.c src/pars_str/get_str.c src/export.c src/exit.c \
		src/pipe/pipe.c src/add_function/add_func.c src/pipe/redirect.c \
		src/pipe/heredoc.c
					
OBJS = $(FILES:%.c=%.o)

$(NAME): $(OBJS) $(LIB_NAME)
	$(CC) $(CFLAGS) $(LIB_NAME) $(OBJS) $(RFLAGS) -o $(NAME)
	

all: $(NAME)

${LIB_NAME}: libft;

libft:
	${MAKE} -C ${LIB_PATH} all

clean:
	$(RM) $(OBJS)
	${MAKE} -C ${LIB_PATH} clean

fclean: clean
	$(RM) $(NAME)
	${MAKE} -C ${LIB_PATH} fclean

.PHONY:all clean fclean re