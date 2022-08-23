NAME = pipex
SRC_DIR = ./srcs
SRCS_NAME	=	main.c \
		list_process.c \
		check_cmd.c \
		check_filepath.c \
		set_perror_exit.c
SRCS		=	${addprefix ${SRC_DIR}/, ${SRCS_NAME}}
OBJS		=	${SRCS:.c=.o}

LIBFT_DIR = ./libft
LIBFT = ${LIBFT_DIR}/libft.a
INCLUDES = -I ./include -I ${LIBFT_DIR}

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

${NAME}:  ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${INCLUDES} -o $@

${LIBFT}:
		make -C ${LIBFT_DIR}

.c.o:
	${CC} ${CFLAGS} $< -c ${INCLUDES} -o $@

clean:
		${MAKE} -C ${LIBFT_DIR} clean
		$(RM) $(OBJS)

fclean:	clean
		${MAKE} -C ${LIBFT_DIR} fclean
		$(RM) ${NAME}

re:		fclean all

.PHONY: all clean fclean re .c.o
