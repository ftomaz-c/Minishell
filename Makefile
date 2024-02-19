NAME := minishell

SRC :=	src/main.c \
		src/tools.c \
		src/error.c \
		src/history.c \
		src/history_utils.c \
		src/prompt.c \
		src/utils/print.c \
		src/lexer/expander.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_split.c \
		src/lexer/lexer_split_utils.c \
		src/parser/parser.c \
		src/builtins/builtins.c \
		src/builtins/pwd.c \
		src/builtins/env.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/mini_exit.c \
		src/builtins/export.c \
		src/builtins/export_utils1.c \
		src/builtins/export_utils2.c \
		src/builtins/export_utils3.c \
		src/builtins/unset.c\
		src/parser/parser_utils.c \
		src/parser/builtins.c \
		src/executor/executor.c \
		src/executor/redirections.c \
		src/executor/here_doc.c \
		src/executor/cmd_exec.c \

OBJ := $(SRC:.c=.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -g

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
