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
					srcs/utils2.c \
					srcs/redirectdup.c \
					srcs/set_up_file.c \
					srcs/env_utils.c \
					srcs/add_list_free.c\
					srcs/childs_function.c\
					srcs/function_childs_need.c\
					srcs/ft_close_exec.c\
					srcs/func_exec_need.c \
					srcs/expand_dollars.c \
					srcs/func_expand_dlr.c\
					srcs/funct_env_expand_dlr.c\
					srcs/print_env.c \
					srcs/do_shlvl.c \
					srcs/clean_string.c



OBJS			=	${SRCS:.c=.o}

CC				=	clang -g

CFLAGS			= -Wall -Werror -Wextra

V				= valgrind 

V_F				= valgrind  --leak-check=full --tool=memcheck \
                                --show-reachable=yes \
                                --track-fds=yes \
                                --errors-for-leak-kinds=all \
                                --show-leak-kinds=all \
                                --trace-children=yes -s \
								--suppressions=ignoreliberror --leak-check=full --show-leak-kinds=all

V_R				= valgrind --suppressions=ignoreliberror --leak-check=full --show-leak-kinds=all --track-fds=no

.c.o			:
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					${CC} ${OBJS} -o ${NAME} -lreadline
#					-./minishell
#					${V_R} ${V_F}  
#					x-terminal-emulator -f -T Minishell -x ./minishell ${V_F}

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
