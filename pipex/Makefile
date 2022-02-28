NAME	= pipex
HEADER	= mandatory/includes/pipex.h gnl/get_next_line.h

HEADER_B= bonus/includes/pipex.h

SRCS	= 	mandatory/src/execution.c mandatory/src/main.c mandatory/src/utils.c

SRCS_B	=	bonus/src/ft_access.c bonus/src/ft_here_doc.c bonus/src/init.c \
			bonus/src/main.c bonus/src/utils.c bonus/src/utils2.c

SRCS_F	= 	functions/ft_split.c functions/ft_strjoin.c functions/ft_substr.c \
			functions/ft_strncmp.c functions/ft_strlen.c \
			functions/ft_strdup.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}
OBJS_F	= ${SRCS_F:.c=.o}

BONUS_CHECK	=	0

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: ${NAME}

%.o : %.c	${HEADER} ${HEADER_B} Makefile
		${CC} ${CFLAGS} -c $< -o $@

ifeq ($(BONUS_CHECK), 0)
$(NAME): ${OBJS} | clean_bonus
else
$(NAME): ${OBJS_B} | clean_mandatory
endif

${NAME}:	${OBJS_F}
		${CC} ${CFLAGS} $^ -o $@

bonus:
	$(MAKE) BONUS_CHECK=1

clean_mandatory:
	@$(RM) $(OBJS)

clean_bonus:
	@$(RM) $(OBJS_B)

clean:
		@rm -f ${OBJS_B}
		@rm -f ${OBJS_F}
		@rm -f ${OBJS}

fclean:	clean
		@rm -f ${NAME}

re:		fclean all

.PHONY: all clean fclean re bonus clean_mandatory clean_bonus