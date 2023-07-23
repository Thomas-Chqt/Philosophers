# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 15:55:42 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/23 14:44:51 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR 	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/.build

SRC			= ${wildcard ${SRCS_DIR}/*.c}
OBJ			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}

memcheck: EXTERNAL_LIBS = -l ft -l memory_leak_detector

CC					 = gcc
CFLAGS				 = -Wall -Wextra -Werror
memcheck: CFLAGS	+= -D MEMCHECK

NAME		= ${ROOT}/philo


.PHONY: all clean fclean re memcheck


all memcheck: ${NAME}

${NAME}: ${OBJ}
	@${CC} -o $@ $^ ${EXTERNAL_LIBS}
	@echo "Executable created at: $@"

clean:
	@rm -rf ${BUILD_DIR}
	@echo "${BUILD_DIR} deleted."

fclean: clean
	@rm -rf ${NAME}
	@echo "${NAME} deleted."

re: fclean all



${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}


#folders
${BUILD_DIR}:
	@mkdir -p $@
	@echo "folder $@ created."