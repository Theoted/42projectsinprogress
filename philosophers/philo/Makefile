# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 13:44:35 by tdeville          #+#    #+#              #
#    Updated: 2022/03/23 08:40:12 by tdeville         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= philo
HEADER	= includes/philo.h

SRCS	=	src/main.c src/ft_atoi.c src/utils.c src/execution.c src/init.c \
			src/utils2.c src/free_all.c

OBJS		= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: ${NAME}

%.o : %.c	${HEADER} Makefile
		${CC} ${CFLAGS} -c $< -o $@


${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o $@ 

clean:
		rm -f ${OBJS}
		

fclean:	clean
		rm -f ${NAME}
		

re:		fclean all

.PHONY: all clean fclean re%
