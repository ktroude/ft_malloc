HOSTTYPE := $(shell uname -m)_$(shell uname -s)

NAME     := libft_malloc_$(HOSTTYPE).so
LINK     := libft_malloc.so

CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -fPIC
INC      := -Iinclude -Ilibft

SRC_DIR  := src
OBJ_DIR  := obj

SRC      := $(wildcard $(SRC_DIR)/*.c)
OBJ      := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_DIR := libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a


all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LIBFT_LIB) $(INC)
	ln -sf $@ $(LINK)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LINK)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
