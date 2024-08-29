NAME = minishell

SRC_PATH = sources
LIBFT_PATH = libraries/libft
READLINE_PATH = libraries/readline

SRC =	$(SRC_PATH)/main.c \
		$(SRC_PATH)/commands.c \
		$(SRC_PATH)/execute.c \
		$(SRC_PATH)/lexer.c \
		$(SRC_PATH)/signals.c \
		$(SRC_PATH)/utils.c \
		$(SRC_PATH)/tokenisator.c

OSRC = 	$(SRC:.c=.o)

CC = cc

INCFLAGS = -I./includes -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

# INCFLAGS = -I./includes -I/*your path to readline*/readline/include
# LDFLAGS = -L/*your path to readline*/readline/lib -lreadline

CFLAGS = -Wall -Wextra -Werror $(INCFLAGS)

LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OSRC) $(LIBFT)
	@$(CC) $(CFLAGS) $(LDFLAGS) ${OSRC} $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OSRC)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re