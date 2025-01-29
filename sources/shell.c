/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 04:25:38 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	shell_init(t_shell *shell)
{
	static const t_clear_info	clear = {0};

	if (__builtin_expect(!shell, 0))
		return (false);
	shell->cmd = NULL;
	return (collection_create(&shell->tokens, sizeof(t_token), 32, clear));
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	collection_destroy(&shell->tokens);
}
