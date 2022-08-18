NAME = pipex

SRCS =	./src/pipex.c \
		./src/list_process.c \
		./src/connect_process.c \
		./src/set_cmd.c \
		./src/set_execve.c \
		./src/set_perror_exit.c

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

OBJS = ${SRCS:.c=.o}

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

HEADER = ./include \
		./libft

all:	${NAME}

${NAME}: ${HEADER} ${LIBFT} ${OBJS}
		$(CC) ${CFLAGS} -I${LIBFT} ${OBJS} -o ${NAME}

${LIBFT}:
		make -C ${LIBFT_DIR}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

clean:
		${MAKE} -C ${LIBFT_DIR} clean
		$(RM) $(OBJS)
		$(RM) ${LIBFT}

fclean:	clean
		${MAKE} -C ${LIBFT_DIR} fclean
		$(RM) ${NAME}

re:		fclean all

.PHONY: all clean fclean re .c.o
