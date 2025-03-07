/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:46:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 04:05:44 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	on_shell_prompt(t_shell *shell, const char *cmd)
{
	if (tokenize(cmd, &shell->tokens))
		return (EXIT_FAILURE);
	if (lalr_parse(&shell->parser, &shell->tokens))
		return (error(E_PARSE_AST,
				((t_token *)collection_get(&shell->tokens, shell->parser.token_id))->val));
	ast_print(shell->parser.ast);
	ft_dprintf(2, "------- output -------\n");
	ft_dprintf(2, "----------------------\n exit status: %d\n",
		evaluate(shell->parser.ast, &shell->env));
	return (E_OK);
}

void	rl_shell_nl(int num)
{
	(void) num;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	rl_shell_prompt(t_shell *shell)
{
	char	*buf;

	buf = readline(rl_readline_name);
	while (buf)
	{
		if (ft_strlen(buf) > 0)
		{
			add_history(buf);
			on_shell_prompt(shell, buf);
		}
		shell_clear(shell);
		rl_readline_name = ft_strjoin(*(char **)hmap_get(&shell->env, "PWD"), " : ");
		free(buf);
		buf = readline(rl_readline_name);
	}
}
