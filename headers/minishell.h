/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:24:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/13 05:45:34 by mrouves          ###   ########.fr       */
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

# define SHELL_PROMPT	"minishell:~$ "
# define HEREDOC_PROMPT	"> "
# define HEREDOC_PATH	"/tmp/.m_heredoc"
# define ENV_MEM 1024

typedef struct s_shell
{
	const char		*name;
	t_collection	tokens;
	t_parser		parser;
	t_hmap			env;
	int				status;
}	t_shell;

int		shell_init(t_shell *shell, const char *name, const char **env);
void	shell_destroy(t_shell *shell);
void	shell_clear(t_shell	*shell);

void	rl_shell_nl_exit(int num);
void	rl_shell_prompt(t_shell *shell);

#endif
