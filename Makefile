# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/16 21:53:10 by fmontser          #+#    #+#              #
#    Updated: 2024/01/29 19:35:18 by fmontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 		+= --silent
MAKEFILE		:= Makefile

INC_DIR			:= include/
SRC_DIR			:= src/
OBJ_DIR			:= obj/
BIN_DIR			:= bin/
NAME			:= philo
HDRS 			:= defs.h
SRCS 			:= main.c init.c utils.c memory.c getsetters.c time.c log.c threads.c actions.c
OBJS			:= $(SRCS:.c=.o)

CC				:= gcc
PERF_FLAGS		:= -O3
CC_FLAGS		:= -Wall -Werror -Wextra -g -c $(PERF_FLAGS)
STD_LIBS		:= -lpthread
TEST_LEAKS		:= leaks -atExit --
TEST_THREADS	:= #-fsanitize=thread
TEST_ARGS		:= 4 410 200 200

CLEAN_TARGETS	= $(wildcard $(addprefix $(OBJ_DIR), $(OBJS)))
FCLEAN_TARGETS	= $(wildcard $(addprefix $(BIN_DIR), $(NAME)))

COLOR_GREEN		:=\033[0;32m
COLOR_RED		:=\033[0;31m
COLOR_BLUE		:=\033[0;34m
COLOR_END		:=\033[0m

vpath %.h $(INC_DIR)
vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath % $(BIN_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(addprefix $(OBJ_DIR),$(OBJS)) -o $(BIN_DIR)$(NAME) $(STD_LIBS) $(TEST_THREADS)
	@echo "$(COLOR_GREEN)write file: $(BIN_DIR)$(NAME)$(COLOR_END)"

%.o : %.c $(HDRS) $(MAKEFILE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I $(INC_DIR) $(CC_FLAGS) $< -o $(OBJ_DIR)$@ $(TEST_THREADS)
	@echo "$(COLOR_GREEN)write file: $(OBJ_DIR)$@ $(COLOR_END)"

test: all
	@./$(BIN_DIR)$(NAME) $(TEST_ARGS)


tleaks: all
	@$(TEST_LEAKS) ./$(BIN_DIR)$(NAME) $(TEST_ARGS)

clean:
	@$(foreach item,$(CLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)

fclean: clean
	@$(foreach item,$(FCLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)

re: fclean all

.PHONY: all clean fclean re
