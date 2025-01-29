/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:24:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 20:44:37 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include <libft.h>
# include <lexer.h>
# include <errors.h>
# include <signals.h>

# define SHELL_PROMPT "shell >> "
# define HERED_PROMPT "heredoc >> "

typedef struct s_shell
{
	const char		*cmd;
	t_collection	tokens;
}	t_shell;

int		shell_init(t_shell *shell);
void	shell_destroy(t_shell *shell);
int		__shell_prompt(t_shell *shell);

void	rl_shell_nl(int);
void	rl_shell_prompt(t_shell *shell, const char *prompt,
			int (*callback)(t_shell *shell));

#endif
