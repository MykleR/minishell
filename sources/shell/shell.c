/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/30 11:54:52 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	shell_init(t_shell *shell, const char *prompt)
{
	static const t_clear_info	clear = {
		(void (*)(void *))token_clear, T_STACK};

	if (__builtin_expect(!shell, 0))
		return (0);
	shell->cmd = NULL;
	shell->prompt = ft_strdup(prompt);
	collection_create(&shell->tokens, sizeof(t_token), 32, clear);
	return (1);
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	alloc_f((void *)shell->prompt);
	collection_destroy(&shell->tokens);
}
