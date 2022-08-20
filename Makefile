NAME = pipex

SRCS =	./srcs/main.c \
		./srcs/list_process.c \
		./srcs/check_cmd.c \
		./srcs/check_filepath.c \
		./srcs/set_perror_exit.c

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft

OBJS = ${SRCS:.c=.o}

CC		= cc

RM		= rm -f

HEADER = ./include/ \
		./libft/

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

${LIBFT}:
		make -C ${LIBFT_DIR}

${NAME}: ${HEADER} ${LIBFT} ${OBJS}
		$(CC) ${CFLAGS} ${LIBFT} ${OBJS} -o ${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${LIBFT_DIR}

clean:
		${MAKE} -C ${LIBFT_DIR} clean
		$(RM) $(OBJS)
		$(RM) ${NAME}
		$(RM) ${LIBFT}

fclean:	clean
		${MAKE} -C ${LIBFT_DIR} fclean
		$(RM) ${NAME}

re:		fclean all

.PHONY: all clean fclean re .c.o
