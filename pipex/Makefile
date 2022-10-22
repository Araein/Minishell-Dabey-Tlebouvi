# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 21:16:46 by tlebouvi          #+#    #+#              #
#    Updated: 2022/10/20 17:22:21 by tlebouvi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= pipex

SRCS_LIST		= main.c \
				pipex.c \
				split.c \
				utils.c \
				getpath.c

SRCS_LIST_BONUS	= ../srcs_bonus/main_bonus.c \
				../srcs_bonus/pipex_bonus.c \
				../srcs_bonus/split_bonus.c \
				../srcs_bonus/utils_bonus.c \
				../srcs_bonus/getpath_bonus.c \
				../srcs_bonus/heredoc_bonus.c \
				../srcs_bonus/multiple_cmd_bonus.c \
				../srcs_bonus/multiple_children_bonus.c \
				../srcs_bonus/init_main_bonus.c

FOLDER			= srcs

FOLDER_BONUS	= srcs_bonus

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

SRCS_BONUS		= $(addprefix ${FOLDER}/, ${SRCS_LIST_BONUS})

OBJS			= ${SRCS:.c=.o}

OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

OBJDIR			= objs

HEADER			= header

CC				= cc  

CFLAGS 			=  -Wall -Wextra -Werror -g

RM				= rm -rf

all:			${NAME}

%.o: %.c
				${CC}   ${CFLAGS}  -I ${HEADER} -o $@ -c $<

$(NAME):		${OBJS}
				${CC} -o ${NAME} ${OBJS}

move:			${OBJS}
				mkdir -p ${OBJDIR} && mv ${OBJS} ${OBJDIR} 

bonus:			fclean ${OBJS_BONUS}
				${CC}  -o ${NAME}  ${OBJS_BONUS}

clean:
				${RM} ${OBJS} ${OBJS_BONUS} ${OUT}

fclean:			clean
				${RM} ${NAME} ${OBJDIR}

re:				fclean all

norminette:		${SRCS} ${SRCS_BONUS}
				norminette header/ft_pipex.h srcs/*.c srcs_bonus/*.c

valgrind:		${NAME}
				@valgrind \
				--leak-check=full --tool=memcheck \
				--show-reachable=yes \
				--track-fds=yes \
				--errors-for-leak-kinds=all \
				--show-leak-kinds=all \
				 --trace-children=yes -s \
				./${NAME} infile cat wc /dev/stdout

.PHONY: 		all fclean clean re norminette valgrind bonus move

# -fsanitize=address -g3 #