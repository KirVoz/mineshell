NAME = minishell

SRC_PATH = sources
ERR_PATH = sources/error_handler
LXR_PATH = sources/lexer
TKN_PATH = sources/lexer/tokenizator
PHD_PATH = sources/lexer/pipe_heredoc
EXP_PATH = sources/lexer/expander
VLD_PATH = sources/lexer/validator
PRS_PATH = sources/lexer/parser
MEM_PATH = sources/memory_managment
EXE_PATH = sources/executor
LIBFT_PATH = libraries/libft
READLINE_PATH = libraries/readline
READLINE_LIB_PATH = $(PWD)/libraries/readline_lib
OBJ_DIR = objects

SRC =	$(SRC_PATH)/main.c \
		$(EXE_PATH)/commands.c \
		$(EXE_PATH)/execute.c \
		$(EXE_PATH)/execute2.c \
		$(EXE_PATH)/execute3.c \
		$(EXE_PATH)/execute4.c \
		$(EXE_PATH)/execute5.c \
		$(EXE_PATH)/execute6.c \
		$(EXE_PATH)/execute7.c \
		$(EXE_PATH)/execute8.c \
		$(EXE_PATH)/exit.c \
		$(EXE_PATH)/exit2.c \
		$(EXE_PATH)/path.c \
		$(EXE_PATH)/pwd.c \
		$(EXE_PATH)/cd1.c \
		$(EXE_PATH)/cd2.c \
		$(EXE_PATH)/env.c \
		$(EXE_PATH)/echo.c \
		$(EXE_PATH)/export.c \
		$(EXE_PATH)/export2.c \
		$(EXE_PATH)/export3.c \
		$(EXE_PATH)/export4.c \
		$(EXE_PATH)/unset.c \
		$(SRC_PATH)/signals.c \
		$(SRC_PATH)/utils.c \
		$(ERR_PATH)/error_handler1.c \
		$(ERR_PATH)/error_handler2.c \
		$(ERR_PATH)/error_handler3.c \
		$(ERR_PATH)/error_handler_utils.c \
		$(LXR_PATH)/lexer.c \
		$(LXR_PATH)/lexer_utils.c \
		$(LXR_PATH)/merger.c \
		$(TKN_PATH)/tokenizator.c \
		$(TKN_PATH)/tokenizator_utils.c \
		$(PHD_PATH)/pipe_heredoc.c \
		$(PHD_PATH)/heredoc_utils.c \
		$(PHD_PATH)/heredoc_expander.c \
		$(PHD_PATH)/pipe_utils.c \
		$(PHD_PATH)/pipe_heredoc_utils.c \
		$(EXP_PATH)/expander.c \
		$(EXP_PATH)/expander_utils1.c \
		$(EXP_PATH)/expander_utils2.c \
		$(EXP_PATH)/expander_len_utils.c \
		$(EXP_PATH)/expander_env_utils.c \
		$(PRS_PATH)/parser.c \
		$(PRS_PATH)/parser_utils.c \
		$(PRS_PATH)/parser_list_utils.c \
		$(PRS_PATH)/parser_postprocessing.c \
		$(VLD_PATH)/validator.c \
		$(VLD_PATH)/validator_utils.c \
		$(MEM_PATH)/shlvl.c \
		$(MEM_PATH)/memory_allocation1.c \
		$(MEM_PATH)/memory_allocation2.c \
		$(MEM_PATH)/memory_deallocation1.c \
		$(MEM_PATH)/memory_deallocation2.c \
		$(MEM_PATH)/minishell_init.c \
		$(LXR_PATH)/general_utils.c \
		$(LXR_PATH)/debug_functions.c 

OSRC = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc

INCFLAGS = -I./includes -I$(READLINE_LIB_PATH)/include/readline/ -DREADLINE_LIBRARY
LDFLAGS = -L$(READLINE_LIB_PATH)/lib -lreadline -lncurses

CFLAGS = -Wall -Wextra -Werror -g $(INCFLAGS)
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address $(INCFLAGS)

LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(READLINE_LIB_PATH) $(OSRC) $(LIBFT)
	@$(CC) $(CFLAGS) ${OSRC} $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "Minishell created"

$(READLINE_LIB_PATH):
	@echo "Configuring readline ..."
	@mkdir -p $(READLINE_LIB_PATH)
	@cd $(READLINE_PATH) && ./configure --prefix=$(READLINE_LIB_PATH) &> /dev/null
	@echo "Installing readline ..."
	@make -C $(READLINE_PATH) install &> /dev/null
	@echo "Readline installed"

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@echo "Libft created"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(READLINE_PATH) --quiet
	@echo "Object files cleaned"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH) 
	@rm -rf $(READLINE_LIB_PATH)
	@echo "Executable and libraries cleaned"

re: fclean all

.PHONY: all clean fclean re

# По традиции линус любит сложности, поэтому может потребоваться библиотека сurses \
для этого при конфигурации readline надо указать флаг --with-curses \
@cd $(READLINE_PATH) && ./configure --prefix=$(READLINE_LIB_PATH) --with-curses &> /dev/null \
а для флагов линковки -lncurses \
LDFLAGS = -L$(READLINE_LIB_PATH)/lib -lreadline -lncurses #
