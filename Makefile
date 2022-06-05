NAME = minishell
LIB_PATH = ./includes/libft/
LIB_NAME = ./includes/libft/libft.a

CC = cc
# gcc -fsanitize=thread флаг для теста потока
CFLAGS = -Wall -Wextra -Werror
RFLAGS = -lreadline -ltermcap -g -L/Users/mmago/.brew/Cellar/readline/8.1.2/lib/ -I/Users/mmago/.brew/Cellar/readline/8.1.2/include
RM = rm -f

FILES = src/main.c
					
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