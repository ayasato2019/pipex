NAME = pipex

SRCS =	./src/pipex.c

LIBFT = ./libft

OBJS = ${SRCS:.c=.o}

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

HEADER = ./include

all:	${NAME} -C ${LIBFT}

${NAME}: ${HEADER} ${OBJS} ${LIBFT}
		$(CC) ${CFLAGS} ${OBJS} -L ${LIBFT} -o ${NAME}

# .c.o:
#		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		${MAKE} -C ${LIBFT} clean
		$(RM) $(OBJS)

fclean:	clean
		${NAME} -C ${LIBFT} fclean
		$(RM) ${NAME}

re:		fclean all

.PHONY: all clean fclean re .c.o
