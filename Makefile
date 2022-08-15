NAME = philo
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -pthread
UNAME = $(shell uname)

SRCS = src/philo.c\
		src/actions.c\
		src/cleanup.c\
		src/errors.c\
		src/init_params.c\
		src/init_philos.c\
		src/libft_utils.c\
		src/monitor.c\
		src/philosophers.c\
		src/print_msg.c\
		src/time.c


ifeq ($(UNAME), Linux)
		MORE_FLAGS = $(CFLAGS) $(LFLAGS)

else
		MORE_FLAGS = $(CFLAGS)

endif

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

RM = rm -rf

all: ${NAME}
${NAME}: $(OBJS)
	$(CC) $(MORE_FLAGS) $(OBJS) -o ${NAME}

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) -f ${NAME} $(OBJS)

re: fclean all

.PHONY: all clean fclean re