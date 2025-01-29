/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 20:57:09 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TEMP FUNCTION, JUST TO PRINT TOKENS LIST
static void __tokens_iter(void *ptr, void *arg)
{
	t_token	*token;
	char	*str;

	str = arg;
	token = ptr;
	if (!token)
		return ;
	ft_printf("%d:[", token->type);
	write(1, str + token->start, token->len);
	ft_printf("], ");
}

int	shell_init(t_shell *shell)
{
	static const t_clear_info	clear = {0};

	if (__builtin_expect(!shell, 0))
		return (0);
	shell->cmd = NULL;
	collection_create(&shell->tokens, sizeof(t_token), 32, clear);
	return (1);
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	collection_destroy(&shell->tokens);
}

int	__shell_prompt(t_shell *shell)
{
	if (tokenize(shell->cmd, &shell->tokens))
		return (E_PARSE_LEX);
	collection_iter(&shell->tokens, (void *)shell->cmd, __tokens_iter);
	collection_clear(&shell->tokens);
	ft_printf("\n");
	return (E_OK);
}
