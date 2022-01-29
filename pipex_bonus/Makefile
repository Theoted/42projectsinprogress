NAME	= pipex
HEADER	= includes/pipex.h libft/libft.h
LIBFT	= Libft

SRCS	=	src/execution.c src/main.c src/utils.c

OBJS		= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: maker ${NAME}

%.o : %.c	${HEADER}
		${CC} ${CFLAGS} -c $< -o $@


${NAME}: ${OBJS} libft/libft.a
		${CC} ${CFLAGS} ${OBJS} -o $@ libft/libft.a

maker:
		${MAKE} -C ${LIBFT}

clean:
		rm -f ${OBJS}
		${MAKE} clean -C ${LIBFT}

fclean:	clean
		rm -f ${NAME}
		${MAKE} fclean -C ${LIBFT}

re:		fclean all

.PHONY: all clean fclean re maker