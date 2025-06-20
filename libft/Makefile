NAME      := libft.a
CC        := gcc
CFLAGS    := -Wall -Wextra -Werror -I. -I../include

SRC_DIR   := .
OBJ_DIR   := obj

SRC       := $(wildcard $(SRC_DIR)/*.c)
OBJ       := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
