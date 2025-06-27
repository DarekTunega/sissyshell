NAME = minishell
CFLAGS = -Wall -Wextra -Werror -MMD -MP
DEBUG_FLAGS = -g -fsanitize=address
CC = cc


SRC_PATH = src/
PARSING_DIR = $(SRC_PATH)parsing/
EXECUTION_DIR = $(SRC_PATH)execution/
BUILTINS_DIR = $(SRC_PATH)builtins/
UTILITIES_DIR = $(SRC_PATH)utilities/
EXPANSION_DIR = $(SRC_PATH)expansion/


INC_DIR = include/
INC_FLAGS = -I$(INC_DIR)


MAIN_SRC = minishell.c minihell.c

PARSING_SRC = parser.c parsing_quotes.c redirection_parser.c tokenize_commands.c \
			  tokenize_arguments.c parsing_utils1.c tokenize_utils.c \
			  redirection_utils.c parsing_utils2.c kingparser.c \

EXECUTION_SRC = executor.c executor_utils.c in_outfiles.c heredoc.c exechelpers.c execsingle.c kokot.c

BUILTINS_SRC = builtin_echo.c builtin_echo_utils.c builtins_cd.c builtin_pwd.c \
			   builtin_export.c builtin_export_utils.c builtin_unset.c \
			   builtin_env.c builtin_exit.c builtins_redirection.c

UTILITIES_SRC = utils.c utils2.c signals.c command_check.c command_check_utils.c

EXPANSION_SRC = env_vars.c env_vars_utils.c


SRC = $(addprefix $(SRC_PATH), $(MAIN_SRC)) \
	  $(addprefix $(PARSING_DIR), $(PARSING_SRC)) \
	  $(addprefix $(EXECUTION_DIR), $(EXECUTION_SRC)) \
	  $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC)) \
	  $(addprefix $(UTILITIES_DIR), $(UTILITIES_SRC)) \
	  $(addprefix $(EXPANSION_DIR), $(EXPANSION_SRC))


OBJ_PATH = obj/
OBJ = $(patsubst $(SRC_PATH)%.c,%.o,$(SRC))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))


DEPS = $(OBJS:.o=.d)


LDFLAGS = -lreadline


LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a


all: $(LIBFT) $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(LIBFT) $(NAME)


$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)


-include $(DEPS)


clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean debug
