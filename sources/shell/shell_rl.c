/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:46:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 17:07:05 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	on_shell_prompt(t_shell *shell, const char *cmd)
{
	int	status;

	if (tokenize(cmd, &shell->tokens)
		|| lalr_parse(&shell->parser, &shell->tokens))
		return (EXIT_FAILURE);
	ast_print(shell->parser.ast);
	ft_dprintf(2, "------- output -------\n");
	status = evaluate(shell->parser.ast, &shell->env);
	ft_dprintf(2, "----------------------\n");
	hmap_set(&shell->env, "?", &(char *){ft_itoa(status)});
	ft_dprintf(2, "[exit status => %s]\n",
			*(char **)hmap_get(&shell->env, "?"));
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
		free(buf);
		buf = readline(rl_readline_name);
	}
}
