/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/24 20:47:21 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	shell_init(t_shell *shell, const char *prompt)
{
	static const t_clear_info	clear_t = {
		(void (*)(void *))token_clear, T_STACK};
	static const t_clear_info	clear_s = {0};
	static const size_t			mem_token = sizeof(t_token);
	static const size_t			mem_trace = sizeof(t_parse_trace);

	if (__builtin_expect(!shell, 0))
		return (0);
	shell->cmd = NULL;
	shell->prompt = ft_strdup(prompt);
	return (collection_create(&shell->tokens, mem_token, 32, clear_t)
		&& collection_create(&shell->parser.stack, mem_trace, 32, clear_s));
}

void	shell_clear(t_shell	*shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	alloc_f((void *)shell->cmd);
	shell->cmd = NULL;
	shell->prompt = SHELL_PROMPT;
	shell->parser.ast = NULL;
	shell->parser.token_id = 0;
	collection_clear(&shell->tokens);
	collection_clear(&shell->parser.stack);
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	alloc_f((void *)shell->prompt);
	collection_destroy(&shell->tokens);
	collection_destroy(&shell->parser.stack);
}
