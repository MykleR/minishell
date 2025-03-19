/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:24:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/19 06:34:16 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <lexer.h>
# include <parser.h>
# include <execution.h>
# include <utils.h>

# define SHELL_PROMPT	"\001\033[96m\002SigmaShell:\001\x1b[0m\002~$ "
# define HEREDOC_PROMPT	"> "
# define HEREDOC_PATH	"/tmp/.m_heredoc"
# define ENV_MEM 1024

typedef struct s_shell
{
	t_collection	tokens;
	t_parser		parser;
	t_hmap			env;
	int				status;
}	t_shell;

int		shell_init(t_shell *shell, const char **env);
void	shell_destroy(t_shell *shell);
void	shell_clear(t_shell	*shell);
void	shell_readline(t_shell *shell);

# define SHELL_BANNER "\033[1m\
┌────────────────────────────────────────────────────────┐\n\
│▓▓▓▓░     ░░░░░░░░░░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓░   ░░░░                ░▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓░   ░░       ░░░▒███▓   ░▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓░ ░ ░░▒▓▓▒▒▒▒▒░░░░████▒░▓▓▓▓▓▓▓▓▓▓  ╔═╗┬┌─┐┌┬┐┌─┐   │\n\
│▓▓▓▓▒ ░ ░░░▒▓█████▓░░░░▓███▓▒▓▓▓▓▓▓▓▓▓  ╚═╗││ ┬│││├─┤   │\n\
│▓▓▓▓▒ ░░░░░░▒██████▒░░░░▒████▓▓▓▓▓▓▓▓▓  ╚═╝┴└─┘┴ ┴┴ ┴   │\n\
│▓▓▓▓▓░░░░░░░░░▓▓████▓▓▓▓▓▓▓█████▓▓▓▓▓▓  ╔═╗┬ ┬┌─┐┬  ┬   │\n\
│▓▓▓▓▓░░▒░░░░░░░▒▒▓▓▓▒▓▒░░░      ░▓▓▓▓▓  ╚═╗├─┤├┤ │  │   │\n\
│▓▓▓▓▓░░▒░▒▒░░░░▒▒▒▓▓░░         ▒▓▓▓▓▓▓  ╚═╝┴ ┴└─┘┴─┘┴─┘ │\n\
│▓▓▓▓▓░░▓░░▓░░░░▒▒▒▓▓▒░       ░▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓░░▓▓▓▓░░░░░▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓▓▒░░░░░░░░░░░▒▓░░        ░▒▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓▓▓▓  ░░░░░░░░░▒▒░░▒▒▒▒▒▒░░▒▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓▓▓▒  ░░░░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓  mrouves         │\n\
│▓▓▓▓▓▓▓░   ░░░░░░░░░▒▒▒▓██████▓▒▓▓▓▓▓▓  thomarna        │\n\
└────────────────────────────────────────────────────────┘\n\
\x1b[0m"

#endif
