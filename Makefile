NAME = pipex

NAMEBONUS = pipex_bonus

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = errors.c \
		main.c \
		ft_split_slash.c \
		pipex_utils.c \
		data.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_intputchar_fd.c \
		ft_intputstr_fd.c \
		ft_printf.c \
		ft_putnbr_base_fd.c \
		ft_sizebase_fd.c \
		ft_strlen.c \
		ft_split.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strncmp.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \

SRCBONUS = errors_bonus.c \
			main_bonus.c \
			ft_split_slash_bonus.c \
			pipex_utils_bonus.c \
			data_bonus.c \
			here_doc1.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_intputchar_fd.c \
			ft_intputstr_fd.c \
			ft_printf.c \
			ft_putnbr_base_fd.c \
			ft_sizebase_fd.c \
			ft_strlen.c \
			ft_split.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strncmp.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \

BONUSDIR = ./bonus/

OBJ = $(SRC:.c=.o)

OBJBONUS = $(addprefix $(BONUSDIR), $(SRCBONUS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(FLAGS) -I ./ $(SRC) -o $@ 

bonus: $(OBJBONUS)
	$(CC) $(FLAGS) -I $(BONUSDIR) $(addprefix $(BONUSDIR), $(SRCBONUS)) -o $(addprefix $(BONUSDIR), $(NAMEBONUS))

clean:
	rm -f $(OBJ) $(OBJBONUS) 

fclean: clean
	rm -f $(NAME) $(addprefix $(BONUSDIR), $(NAMEBONUS))

re: fclean all
