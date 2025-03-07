/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 01:29:34 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	shell_init(t_shell *shell, const char *name, const char **env)
{
	static const t_clear_info	clear_t = {
		(void (*)(void *))token_clear, T_STACK};
	static const t_clear_info	clear_s = {0};
	static const t_clear_info	clear_e = {alloc_f, T_HEAP};

	if (__builtin_expect(!shell || shell_sig_set(), 0))
		return (E_ERROR);
	shell->name = ft_strdup(name);
	collection_init(&shell->tokens, sizeof(t_token), 32, clear_t);
	collection_init(&shell->parser.stack, sizeof(t_parse_trace), 32, clear_s);
	hmap_init(&shell->env, ENV_MEM, sizeof(char **), clear_e);
	env_init(&shell->env, env);
	return (E_OK);
}

int	shell_sig_set(void)
{
	return (sig_handle(SIGINT, (t_sig_callb)rl_shell_nl, SIG_SIMPLE)
		|| sig_handle(SIGQUIT, (t_sig_callb){0}, SIG_IGNORE));
}

int	shell_sig_reset(void)
{
	return (sig_handle(SIGINT, (t_sig_callb){0}, SIG_RESTORE)
		|| sig_handle(SIGQUIT, (t_sig_callb){0}, SIG_RESTORE));
}

void	shell_clear(t_shell	*shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	collection_clear(&shell->tokens);
	collection_clear(&shell->parser.stack);
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	alloc_f((void *)shell->name);
	collection_destroy(&shell->tokens);
	collection_destroy(&shell->parser.stack);
	collection_destroy(&shell->env);
}
