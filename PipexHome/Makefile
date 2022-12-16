NAME = pipex

CC = gcc

FLAGS = -Wall -Wextra -Werror -I

SRC = errors.c \
		ft_split_slash.c \
		main.c \
		pipex_utils.c \
		pipex.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -c $^ -o $@ libft.a 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all