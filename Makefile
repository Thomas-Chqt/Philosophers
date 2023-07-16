# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 15:55:42 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/14 17:41:36 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR 	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/.build

SRC			= ${wildcard ${SRCS_DIR}/*.c}
OBJ			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}
OBJ_DEBUG	= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=_debug.o}}

CC						= gcc
CFLAGS					= -Wall -Wextra -Werror
alldebug: CFLAGS		= -g -D MEMCHECK

NAME		= ${ROOT}/philo
NAME_DEBUG	= ${ROOT}/philo_debug

vpath %.c ${ROOT} ${SRCS_DIR}


.PHONY: all clean fclean re debug cleandebug fcleandebug redebug norm cleanbuild


all: ${NAME}

${NAME}: ${OBJ}
	@${CC} -o $@ $^ ${EXTERNAL_LIBS}
	@echo "Executable created at $@."

clean:
	@rm -rf ${OBJ}
	@echo "Release object files deleted."

fclean: clean
	@rm -rf ${NAME}
	@echo "${NAME} deleted."

re: fclean all




debug: ${NAME_DEBUG}

${NAME_DEBUG}: ${OBJ_DEBUG}
	@${CC} -o $@ $^ ${EXTERNAL_LIBS}
	@echo "Executable created at $@."

cleandebug:
	@rm -rf ${OBJ_DEBUG}
	@echo "Debug object in ${BUILD_DIR} files deleted."

fcleandebug: cleandebug
	@rm -rf ${NAME_DEBUG}
	@echo "${NAME_DEBUG} deleted."

redebug: fcleandebug debug




norm:
	@norminette ${SRCS_DIR} ${INCLUDES_DIR}


cleanbuild:
	@rm -rf ${BUILD_DIR}
	@echo "Build folder deleted."



${BUILD_DIR}/%_debug.o ${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}


#folders
${BUILD_DIR}:
	@mkdir -p $@
	@echo "folder $@ created."