# replace C_FILES with hard coded path i.e. make a bash script
C_FILES = $(wildcard ./*.c)
O_FILES = $(C_FILES:%.c=build/%.o)
C_FLAGS = -Wall -Werror -Wextra
NAME = fractol

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	$(CC) -O3 $^ -o $(NAME) -L ./42_MyLibC -lft -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lz

%.o: %.c 
	$(CC)  -O3 -c $< -o $@

build:
	mkdir -p build
	wget https://cdn.intra.42.fr/document/document/23835/minilibx-linux.tgz && tar -xvf minilibx-linux.tgz && rm minilibx-linux.tgz 
	$(MAKE) -C 42_MyLibC
	$(MAKE) -C minilibx-linux

clean:
	rm -rf build
	$(MAKE) -C 42_MyLibC clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C 42_MyLibC fclean


re: fclean all
