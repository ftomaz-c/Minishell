#include "../../includes/lexer.h"

/**
 * @brief Displays a syntax error message.
 * 
 * This function displays a syntax error message indicating the unexpected token.
 * 
 * @param token The unexpected token.
 * 
 * @return None.
 * 
 * @note None.
 * 
 * @warning None.
 * 
 * @see None.
 * 
 * @example
 * ```
 * syntax_err('$');
 * // Displays "bash: syntax error near unexpected token '$'"
 * ```
 */
void	syntax_err(char token)
{
	g_status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}