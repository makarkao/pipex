SRCS = commands_handler.c command_handler_tools.c pipex_clean_tools.c heredoc_handler.c pipes_flow_handler.c get_next_line.c \

SRCSM = pipex_init.c pipex.c \

SRCSB = pipex_init_bonus.c pipex_bonus.c \

OBJS = ${SRCS:.c=.o}
OBJSM = ${SRCSM:.c=.o}
OBJSB = ${SRCSB:.c=.o}


NAME = pipex
BONUS = pipex_bonus
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -L ./libft -lft
CMAKE = make -C

LIBFTDIR = libft/

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -g

${NAME}: ${OBJS} ${OBJSM}
	${CMAKE} ${LIBFTDIR}
	${CC} ${CFLAGS} ${OBJS} ${OBJSM} -o ${NAME} ${INCLUDE} -g

${BONUS}: ${OBJS} ${OBJSB}
	${CMAKE} ${LIBFTDIR}
	${CC} ${CFLAGS} ${OBJS} ${OBJSB} -o ${BONUS} ${INCLUDE} -g

bonus: ${BONUS}

clean:
	${CMAKE} ./libft clean
	${RM} ${OBJS} ${OBJSB} ${OBJSM}

fclean: clean
	${CMAKE} ./libft fclean
	${RM} ${NAME} ${BONUS}

re: fclean all

.PHONY: all clean fclean re bonus
