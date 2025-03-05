/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:46:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 22:21:02 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	on_shell_prompt(t_shell *shell)
{
	if (tokenize(shell->cmd, &shell->tokens))
		return (E_PARSE_LEX);
	if (lalr_parse(&shell->parser, &shell->tokens))
		return (E_PARSE_AST);
	//ast_print(shell->parser.ast);
	printf("exit status: %d\n",evaluate(shell->parser.ast));
	return (E_OK);
}

void	rl_shell_nl(int num)
{
	(void) num;
	write(1, "\n", 1);
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
		shell->cmd = ft_strdup(buf);
		free(buf);
		if (ft_strlen(shell->cmd) > 0)
		{
			add_history(shell->cmd);
			error_print(on_shell_prompt(shell));
		}
		shell_clear(shell);
		buf = readline(rl_readline_name);
	}
}
