# replace C_FILES with hard coded path i.e. make a bash script
C_FILES = $(wildcard ./*.c)
C_FLAGS = -Wall -Werror -Wextra
NAME = fractol

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc $(C_FLAGS) $^ -o $(NAME) -L ./libft -lft

build:
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C libft fclean


re: fclean all
