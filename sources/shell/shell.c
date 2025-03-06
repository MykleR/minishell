/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/06 00:21:36 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	shell_init(t_shell *shell, const char *prompt, const char **env)
{
	static const t_clear_info	clear_t = {
		(void (*)(void *))token_clear, T_STACK};
	static const t_clear_info	clear_s = {0};
	static const t_clear_info	clear_e = {alloc_f, T_HEAP};

	if (__builtin_expect(!shell || shell_sig_set(), 0))
		return (E_SYS_SIG);
	shell->cmd = NULL;
	shell->name = ft_strdup(prompt);
	collection_create(&shell->tokens, sizeof(t_token), 32, clear_t);
	collection_create(&shell->parser.stack, sizeof(t_parse_trace), 32, clear_s);
	hm_create(&shell->env, ENV_MEM, sizeof(char **), clear_e);
	env_init(&shell->env, env);
	return (E_OK);
}

int	shell_sig_set(void)
{
	if (sig_handle(SIGINT, (t_sig_callb)rl_shell_nl, SIG_SIMPLE)
		|| sig_handle(SIGQUIT, (t_sig_callb){0}, SIG_IGNORE))
		return (E_SYS_SIG);
	return (E_OK);
}

int	shell_sig_reset(void)
{
	if (sig_handle(SIGINT, (t_sig_callb){0}, SIG_RESTORE)
		|| sig_handle(SIGQUIT, (t_sig_callb){0}, SIG_RESTORE))
		return (E_SYS_SIG);
	return (E_OK);
}

void	shell_clear(t_shell	*shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	alloc_f((void *)shell->cmd);
	shell->cmd = NULL;
	shell->parser.ast = NULL;
	shell->parser.token_id = 0;
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
