NAME = minishell

SRC_PATH = sources
LXR_PATH = sources/lexer
EXE_PATH = sources/executor
LIBFT_PATH = libraries/libft
READLINE_PATH = libraries/readline
OBJ_DIR = objects

SRC =	$(SRC_PATH)/main.c \
		$(EXE_PATH)/commands.c \
		$(EXE_PATH)/execute.c \
		$(EXE_PATH)/path.c \
		$(EXE_PATH)/pwd.c \
		$(EXE_PATH)/unset.c \
		$(SRC_PATH)/signals.c \
		$(SRC_PATH)/utils.c \
		$(SRC_PATH)/error_handler.c \
		$(LXR_PATH)/lexer.c \
		$(LXR_PATH)/pipe_heredoc.c \
		$(LXR_PATH)/heredoc_utils.c \
		$(LXR_PATH)/pipe_heredoc_utils.c \
		$(LXR_PATH)/tokenizator.c \
		$(LXR_PATH)/tokenizator_utils.c \
		$(LXR_PATH)/expander.c \
		$(LXR_PATH)/expander_utils.c \
		$(LXR_PATH)/expander_env_utils.c \
		$(LXR_PATH)/parser.c \
		$(LXR_PATH)/parser_utils.c \
		$(LXR_PATH)/parser_list_utils.c \
		$(LXR_PATH)/validator.c \
		$(LXR_PATH)/validator_utils.c \
		$(LXR_PATH)/memory_managment.c \
		$(LXR_PATH)/general_utils.c \
		$(LXR_PATH)/debug_functions.c 

OSRC = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc

INCFLAGS = -I./includes -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

# INCFLAGS = -I./includes -I/*your path to readline*/readline/include
# LDFLAGS = -L/*your path to readline*/readline/lib -lreadline

# CFLAGS = -Wall -Wextra -Werror -g $(INCFLAGS)
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address $(INCFLAGS)

LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OSRC) $(LIBFT)
	@$(CC) $(CFLAGS) ${OSRC} $(LIBFT) -o $(NAME) $(LDFLAGS) 

$(LIBFT):
	@make -C $(LIBFT_PATH)

ex: re #to go into file after re 
	./minishell

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re