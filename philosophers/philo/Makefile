# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 13:44:35 by tdeville          #+#    #+#              #
#    Updated: 2022/03/04 15:35:34 by tdeville         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= philo
HEADER	= includes/philo.h

SRCS	=	src/main.c src/ft_atoi.c src/utils.c src/execution.c

OBJS		= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: ${NAME}

%.o : %.c	${HEADER}
		${CC} -fsanitize=thread ${CFLAGS} -c $< -o $@


${NAME}: ${OBJS}
		${CC} -fsanitize=thread ${CFLAGS} ${OBJS} -o $@ 

clean:
		rm -f ${OBJS}
		

fclean:	clean
		rm -f ${NAME}
		

re:		fclean all

.PHONY: all clean fclean re%