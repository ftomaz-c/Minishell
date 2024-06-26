NAME := minishell

SRC :=	src/main.c \
		src/minishell/minishell.c \
		src/minishell/signals.c \
		src/minishell/tools.c \
		src/minishell/tools_utils1.c \
		src/minishell/tools_utils2.c \
		src/utils/error.c \
		src/utils/history.c \
		src/utils/history_utils.c \
		src/utils/prompt.c \
		src/utils/print.c \
		src/utils/utils1.c \
		src/utils/utils2.c \
		src/utils/utils3.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils1.c \
		src/lexer/lexer_utils2.c \
		src/lexer/lexer_utils3.c \
		src/lexer/lexer_split.c \
		src/lexer/lexer_split_utils.c \
		src/expander/expander.c \
		src/expander/expander_utils1.c \
		src/expander/expander_utils2.c \
		src/expander/expander_split.c \
		src/builtins/builtins.c \
		src/builtins/cmd_pwd.c \
		src/builtins/cmd_env.c \
		src/builtins/cmd_echo.c \
		src/builtins/cmd_exit.c \
		src/builtins/cmd_cd/cmd_cd.c \
		src/builtins/cmd_cd/cmd_cd_utils.c \
		src/builtins/cmd_export/cmd_export.c \
		src/builtins/cmd_export/cmd_export_utils1.c \
		src/builtins/cmd_export/cmd_export_utils2.c \
		src/builtins/cmd_export/cmd_export_utils3.c \
		src/builtins/cmd_unset.c\
		src/builtins/cmd_history/cmd_history.c \
		src/builtins/cmd_history/cmd_history_utils.c \
		src/parser/parser.c \
		src/parser/parser_redir.c \
		src/parser/parser_utils.c \
		src/executor/executor.c \
		src/executor/executor_utils1.c \
		src/executor/executor_utils2.c \
		src/executor/redirections.c \
		src/executor/redirections_utils.c \
		src/executor/here_doc.c \
		src/executor/pipex.c \
		src/executor/child_signals.c \

OBJ := $(SRC:.c=.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -g #-fsanitize=address

INCLUDES := -I.libft/includes

LIBFT := libft/libft.a

GREEN := \033[0;32m
CYAN := \033[0;36m
RED := \033[0;31m
NC := \033[0m

all:	$(LIBFT) $(OBJ) $(NAME)

$(LIBFT):
	@echo "$(CYAN)\n# Compiling libft...\n$(NC)"
	@$(MAKE) -C libft || (rm -f $(NAME)  && exit 1)

	@echo "$(CYAN)\n# Compiling $(NAME)...\n$(NC)"
	@echo "cc -Wall -Wextra -Werror -g -I./libft/includes -c *.c -o *.o"

$(OBJ): %.o: %.c
	@echo "$(CYAN)	Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(CYAN)\n# Linking $(NAME) with libft...\n$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)\n###############################$(NC)"
	@echo "$(GREEN)	$(NAME) is ready!$(NC)"
	@echo "$(GREEN)###############################$(NC)"

v:
	$(MAKE) fclean && $(MAKE) && valgrind --log-file="valgrind.txt" -s --leak-check=full --show-leak-kinds=all --suppressions=supp_rl --track-origins=yes --track-fds=yes  ./$(NAME)

clean:
	@echo "$(CYAN)\n# Cleaning libft...\n$(NC)"
	$(MAKE) -C libft clean
	@echo "$(CYAN)\n# Cleaning object files...\n$(NC)"
	rm -f $(OBJ)
	@echo "$(GREEN)\n###########################################$(NC)"
	@echo "$(GREEN)	$(NAME) object files cleaned!$(NC)"
	@echo "$(GREEN)###########################################$(NC)"

fclean: clean
	@echo "$(CYAN)\n# Cleaning $(NAME) and libft...\n$(NC)"
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	@echo "$(GREEN)\n########################################$(NC)"
	@echo "$(GREEN)	$(NAME) and libft cleaned!$(NC)"
	@echo "$(GREEN)########################################$(NC)"

re: fclean all

.PHONY: all clean fclean re
