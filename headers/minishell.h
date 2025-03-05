/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:24:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 17:19:04 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <lexer.h>
# include <parser.h>
# include <execution.h>
# include <utils.h>

# define SHELL_PROMPT "shell >> "
# define HERED_PROMPT "heredoc >> "

typedef struct s_shell
{
	const char		*cmd;
	const char		*prompt;
	t_collection	tokens;
	t_parser		parser;
}	t_shell;

int		shell_init(t_shell *shell, const char *prompt);
void	shell_destroy(t_shell *shell);
void	shell_clear(t_shell	*shell);
int		shell_sig_set(void);
int		shell_sig_reset(void);

void	rl_shell_nl(int num);
void	rl_shell_prompt(t_shell *shell);

ssize_t	safe_read(int fd, void *buffer, size_t count);
ssize_t	safe_write(int fd, const void *buffer, size_t count);

#endif
