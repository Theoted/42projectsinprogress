NAME	= pipex
HEADER	= mandatory/includes/pipex.h libft/libft.h

HEADER_B= bonus/includes/pipex.h libft/libft.h

LIBFT	= libft

SRCS	= 	mandatory/src/execution.c mandatory/src/main.c mandatory/src/utils.c

SRCS_B	=	bonus/src/ft_access.c bonus/src/ft_here_doc.c bonus/src/init.c \
			bonus/src/main.c bonus/src/utils.c \

OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: maker ${NAME}

%.o : %.c	${HEADER}
		${CC} ${CFLAGS} -c $< -o $@


${NAME}:${OBJS} libft/libft.a
		${CC} ${CFLAGS} ${OBJS} -o $@ libft/libft.a

maker:
		${MAKE} -C ${LIBFT}

bonus:	maker ${OBJS_B} libft/libft.a
		${CC} ${CFLAGS} ${OBJS_B} -o pipex libft/libft.a

clean:
		@rm -f ${OBJS_B}
		@rm -f ${OBJS}
		${MAKE} clean -C ${LIBFT}

fclean:	clean
		@rm -f ${NAME}
		${MAKE} fclean -C ${LIBFT}

re:		fclean all

.PHONY: all clean fclean re maker