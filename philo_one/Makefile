.PHONY: all
.DEFAULT_GOAL: all

NAME = philo_one

all: $(NAME)

INC_DIR = ./inc/

SRC = \
	main.c \
	ph_fork_action.c \
	ph_lifecycle.c \
	ph_over.c \
	ph_philosopher.c \
	ph_print_err.c \
	ph_print_mutex.c \
	ph_print_util.c \
	ph_run_thread.c \
	ph_table.c \
	ph_time.c \
	ph_util.c
SRC_DIR = src
SRCS_DIR = ./$(SRC_DIR)/
SRCS = $(addprefix $(SRCS_DIR), $(SRC))

OBJ = $(SRC:%.c=%.o)
OBJ_DIR = obj
OBJS_DIR = ./$(OBJ_DIR)/
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

CC = gcc
MKDIR = mkdir

CFLAGS = -Wall -Werror -Wextra -pthread #$(DEBUGF)
DEBUGF = -g3 -fsanitize=address
IFLAGS = -I$(INC_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all