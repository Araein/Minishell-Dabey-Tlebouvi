NAME			=	minishell

SRCS			=	srcs/minishell.c \
					srcs/utils.c \
					srcs/env_management.c \
					srcs/export.c \
					srcs/dollars.c \
					srcs/unset.c \
					srcs/split_pipe.c\
					srcs/split_space.c \
					srcs/command.c \
					srcs/execution.c \
					srcs/itoa.c \
					srcs/builtin_management.c \
					srcs/echo.c \
					srcs/redirect.c \
					parsing/pars_quote.c \
					parsing/token.c \
					parsing/redi_token.c


OBJS			=	${SRCS:.c=.o}

CC				=	clang -g #-Weverything -fsanitize=thread -g

CFLAGS			= -Wall -Werror -Wextra

V				= valgrind 

V_F				= valgrind  --leak-check=full --tool=memcheck \
                                --show-reachable=yes \
                                --track-fds=yes \
                                --errors-for-leak-kinds=all \
                                --show-leak-kinds=all \
                                --trace-children=yes -s \
								--suppressions=ignoreliberror --leak-check=full --show-leak-kinds=all
# --track-fds=yes

V_R				= valgrind --suppressions=ignoreliberror --leak-check=full --show-leak-kinds=all --track-fds=no

.c.o			:
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					${CC} ${OBJS} -o ${NAME} -lreadline
					- ${V_F} ./minishell
                    #${V_R}
#					x-terminal-emulator -f -T Minishell -x ./minishell  

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
