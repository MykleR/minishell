/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/26 13:32:04 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	shell_command(t_shell *shell, const char *cmd)
{
	int	status;

	if (tokenize_cmd(cmd, &shell->tokens))
		return (2);
	if (heredoc_parse(&shell->tokens, &shell->heredocs, &shell->env, &status))
		return (status);
	if (lalr_parse(&shell->parser, &shell->tokens))
		return (2);
	return (evaluate(shell->parser.ast, &shell->env));
}

static void	shell_clear(t_shell	*shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	g_sigint = 0;
	collection_clear(&shell->tokens);
	collection_clear(&shell->parser.stack);
	collection_clear(&shell->heredocs);
	ast_free(shell->parser.ast);
	shell->parser.ast = NULL;
}

void	shell_init(t_shell *shell, const char **env)
{
	const t_clear_info	clear_t = {(void (*)(void *))token_clear, T_STACK};
	const t_clear_info	clear_h = {__heredoc_destroy, T_STACK};
	const t_clear_info	clear_e = {alloc_f, T_HEAP};
	const t_clear_info	clear_s = {0};

	sig_set(sig_callb_newline);
	collection_init(&shell->tokens, sizeof(t_token), 32, clear_t);
	collection_init(&shell->heredocs, sizeof(char **), 32, clear_h);
	collection_init(&shell->parser.stack, sizeof(t_parse_trace), 32, clear_s);
	hmap_init(&shell->env, ENV_MEM, sizeof(char **), clear_e);
	env_init(&shell->env, env);
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	collection_destroy(&shell->tokens);
	collection_destroy(&shell->parser.stack);
	collection_destroy(&shell->env);
	collection_destroy(&shell->heredocs);
	ast_free(shell->parser.ast);
}

void	shell_process(t_shell *shell)
{
	static char		*buf = (char *)1;

	while (buf)
	{
		buf = readline(rl_readline_name);
		if (g_sigint)
			shell->status = g_sigint;
		hmap_set(&shell->env, "?", &(char *){ft_itoa(shell->status)});
		if (ft_strlen(buf) > 0)
		{
			add_history(buf);
			sig_ignore();
			shell->status = shell_command(shell, buf);
			sig_set(sig_callb_newline);
		}
		shell_clear(shell);
		free(buf);
	}
}
