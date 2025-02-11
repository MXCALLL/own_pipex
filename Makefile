SRCS = mandatory/pipex.c mandatory/ft_split.c mandatory/errors.c mandatory/utils.c mandatory/strjoin_helpers.c
SRCSB = bonus/pipex_bonus.c bonus/ft_split_bonus.c bonus/errors_bonus.c bonus/utils_bonus.c bonus/strjoin_helpers_bonus.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS = ${SRCS:.c=.o}
OBJSB = ${SRCSB:.c=.o}
NAME = pipex
NAMEB = pipex_bonus
HEADER = mandatory/pipex.h
HEADER_Bonus = bonus/pipex_bonus.h

all: ${NAME}

${NAME}: ${OBJS}
	@echo "Linking objects into ${NAME}"
	@${CC} ${OBJS} -o ${NAME}

bonus: ${NAMEB}

${NAMEB}: ${OBJSB}
	@echo "Linking objects into ${NAMEB}"
	@${CC} ${OBJSB} -o ${NAMEB}

mandatory/%.o: mandatory/%.c ${HEADER}
	@echo "Compiling source: $<"
	@${CC} ${CFLAGS} -c $< -o $@

bonus/%.o: bonus/%.c ${HEADER_Bonus}
	@echo "Compiling source: $<"
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "Removing all object file"
	@${RM} ${OBJS} ${OBJSB}

fclean: clean
	@echo "Removing ${NAME} or ${NAMEB}"
	@${RM} ${NAME} ${NAMEB}

re: fclean all