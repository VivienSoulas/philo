NAME	=	philo
SRC		=	philo.c \
			table.c \
			routine.c \
			clean_up.c \
			utils.c \
			time.c

OBJ_DIR	=	objects
OBJ		=	$(SRC:%.c=$(OBJ_DIR)/%.o)

CC		=	cc
CFLAGS	=	-Werror -Wall -Wextra -g -pthread
TSAN_FLAG =  -fsanitize=thread

# ANSI color codes
BLACK	=	\033[38;2;0;0;0m
RED		=	\033[38;2;255;0;0m
GREEN	=	\033[38;2;0;128;0m
YELLOW	=	\033[38;2;255;255;0m
BLUE	=	\033[38;2;0;0;255m
LIME	=	\033[38;2;0;255;0m
RESET	=	\033[0m # No Color

# compile source files into object files in a directory
$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# compile with ThreadSanitizer
$(OBJ_DIR)/tsan_%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(TSAN_FLAGS) -c $< -o $@

# instructions to make NAME
$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(LIME)==========================\nSUCCESS : Program compiled\n==========================\n$(RESET)"

tsan: $(SRC:%.c=$(OBJ_DIR)/tsan_%.o)
	@$(CC) $(CFLAGS) $(TSAN_FLAGS) $^ -o $(NAME)_tsan
	@echo "$(YELLOW)===============================\nSUCCESS : ThreadSanitizer build\n===============================\n$(RESET)"

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)/!\ Objects files removed /!\ $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME)_tsan
	@echo "$(RED)/!\ Executable removed /!\ $(RESET)"

re: fclean all

PHONY: all clean fclean re tsan