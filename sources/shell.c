/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:22:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/17 19:44:16 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	on_shell_prompt(t_shell *shell, const char *cmd)
{
	if (tokenize(cmd, &shell->tokens)
		|| heredoc_parse(&shell->tokens)
		|| lalr_parse(&shell->parser, &shell->tokens))
		return ;
	shell->status = evaluate(shell->parser.ast, &shell->env);
	hmap_set(&shell->env, "?", &(char *){ft_itoa(shell->status)});
}

int	shell_init(t_shell *shell, const char **env)
{
	static const t_clear_info	clear_t = {
		(void (*)(void *))token_clear, T_STACK};
	static const t_clear_info	clear_s = {0};
	static const t_clear_info	clear_e = {alloc_f, T_HEAP};

	sig_set();
	collection_init(&shell->tokens, sizeof(t_token), 32, clear_t);
	collection_init(&shell->parser.stack, sizeof(t_parse_trace), 32, clear_s);
	hmap_init(&shell->env, ENV_MEM, sizeof(char **), clear_e);
	env_init(&shell->env, env);
	return (E_OK);
}

void	shell_clear(t_shell	*shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	shell->status = 0;
	collection_clear(&shell->tokens);
	collection_clear(&shell->parser.stack);
	ast_free(shell->parser.ast);
	shell->parser.ast = NULL;
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	collection_destroy(&shell->tokens);
	collection_destroy(&shell->parser.stack);
	collection_destroy(&shell->env);
	ast_free(shell->parser.ast);
}

void	shell_readline(t_shell *shell)
{
	char	*buf;

	buf = readline(rl_readline_name);
	while (buf)
	{
		if (ft_strlen(buf) > 0)
		{
			add_history(buf);
			sig_ignore();
			on_shell_prompt(shell, buf);
			sig_set();
		}
		shell_clear(shell);
		free(buf);
		buf = readline(rl_readline_name);
	}
}
