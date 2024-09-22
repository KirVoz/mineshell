NAME = minishell

SRC_PATH = sources
LXR_PATH = sources/lexer
TKN_PATH = sources/lexer/tokenizator
PHD_PATH = sources/lexer/pipe_heredoc
EXP_PATH = sources/lexer/expander
VLD_PATH = sources/lexer/validator
PRS_PATH = sources/lexer/parser
EXE_PATH = sources/executor
LIBFT_PATH = libraries/libft
READLINE_PATH = libraries/readline
OBJ_DIR = objects

SRC =	$(SRC_PATH)/main.c \
		$(SRC_PATH)/minishell_init.c \
		$(EXE_PATH)/commands.c \
		$(EXE_PATH)/execute.c \
		$(EXE_PATH)/path.c \
		$(EXE_PATH)/pwd.c \
		$(EXE_PATH)/cd.c \
		$(EXE_PATH)/unset.c \
		$(SRC_PATH)/signals.c \
		$(SRC_PATH)/utils.c \
		$(SRC_PATH)/error_handler.c \
		$(LXR_PATH)/lexer.c \
		$(LXR_PATH)/lexer_utils.c \
		$(TKN_PATH)/tokenizator.c \
		$(TKN_PATH)/tokenizator_utils.c \
		$(PHD_PATH)/pipe_heredoc.c \
		$(PHD_PATH)/heredoc_utils.c \
		$(PHD_PATH)/pipe_heredoc_utils.c \
		$(EXP_PATH)/expander.c \
		$(EXP_PATH)/expander_utils.c \
		$(EXP_PATH)/expander_env_utils.c \
		$(PRS_PATH)/parser.c \
		$(PRS_PATH)/parser_utils.c \
		$(PRS_PATH)/parser_list_utils.c \
		$(VLD_PATH)/validator.c \
		$(VLD_PATH)/validator_utils.c \
		$(LXR_PATH)/memory_managment.c \
		$(LXR_PATH)/general_utils.c \
		$(LXR_PATH)/debug_functions.c 

OSRC = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc

INCFLAGS = -I./includes -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

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