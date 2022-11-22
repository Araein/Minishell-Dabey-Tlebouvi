NAME			=	minishell

SRCS			=	srcs/minishell.c \
					srcs/utils.c \
					srcs/env_management.c \
					srcs/export.c \
					srcs/parser.c \
					srcs/dollars.c \
					srcs/unset.c \
					srcs/split_func.c \
					srcs/split_space_utils.c 

OBJS			=	${SRCS:.c=.o}

CC				=	clang #-Weverything -fsanitize=thread -g

CFLAGS			= -Wall -Werror -Wextra

V				= valgrind 

V_F				= valgrind  --leak-check=full --tool=memcheck \
                                --show-reachable=yes \
                                --track-fds=no \
                                --errors-for-leak-kinds=all \
                                --show-leak-kinds=all \
                                --trace-children=yes -s \
								--suppressions=ignoreliberror --leak-check=full --show-leak-kinds=all
# --track-fds=yes

V_R				= valgrind --suppressions=ignoreliberror --leak-check=full --show-leak-kinds=all --track-fds=yes

.c.o			:
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					${CC} ${OBJS} -o ${NAME} -lreadline && ${V_F} ./minishell 
                    
#					x-terminal-emulator -f -T Minishell -x ./minishell

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
