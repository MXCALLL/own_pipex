SRCS = mandatory/pipex.c mandatory/ft_split.c mandatory/errors.c mandatory/utils.c mandatory/strjoin_helpers.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS = ${SRCS:.c=.o}
NAME = pipex
HEADER = mandatory/pipex.h

all: ${NAME}

${NAME}: ${OBJS}
	@echo "Linking objects into ${NAME}"
	@${CC} ${OBJS} -o ${NAME}

mandatory/%.o: mandatory/%.c ${HEADER}
	@echo "Compiling source: $<"
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "Removing all object file"
	@${RM} ${OBJS}

fclean: clean
	@echo "Removing ${NAME}"
	@${RM} ${NAME}

re: fclean all