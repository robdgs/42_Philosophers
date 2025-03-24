NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f
SRCS = main.c philo_parser.c utils.c philo_creator.c guardians.c

all:	${NAME}

${NAME}: ${SRCS}
	${CC}	${CFLAGS}	${SRCS} -o ${NAME}	


clean:
	${RM}

fclean:	clean
	${RM}	${NAME}

re:	fclean	all

.PHONY:	all	clean	fclean	re