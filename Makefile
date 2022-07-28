NAME = pipex

SRCS =	./src/pipex.c \
	./src/set_cmd.c \
	./src/set_perror_exit.c

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

PRINTF = ./printf/printf.a

PRINTF_DIR = ./printf

OBJS = ${SRCS:.c=.o}

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

HEADER = ./include \
	./libft \
	./printf/include

all:	${NAME}

${NAME}: ${HEADER} ${LIBFT} ${PRINTF} ${OBJS}
	$(CC) ${CFLAGS} ${LIBFT} ${PRINTF} ${OBJS} -o ${NAME}

${LIBFT}:
	make -C ${LIBFT_DIR}

${PRINTF}:
	make -C ${PRINTF_DIR}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${LIBFT_DIR} ${PTINTF_DIR}

clean:
	${MAKE} -C ${LIBFT_DIR} -C ${PRINTF} clean
	$(RM) $(OBJS)
	$(RM) ${NAME}
	$(RM) ${LIBFT}
	$(RM) ${PRINTF}

fclean:	clean
	${MAKE} -C ${LIBFT_DIR} fclean


re:		fclean all

.PHONY: all clean fclean re .c.o
