/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:24:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/14 06:02:21 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <lexer.h>
# include <parser.h>
# include <execution.h>
# include <utils.h>

# define SHELL_PROMPT	"\033[96m\033[1mSigmaShell:\x1b[0m~$ "
# define HEREDOC_PROMPT	"\x1b[1m> \x1b[0m"
# define HEREDOC_PATH	"/tmp/.m_heredoc"
# define ENV_MEM 1024

typedef struct s_shell
{
	const char		*name;
	t_collection	tokens;
	t_collection	heredocs;
	t_parser		parser;
	t_hmap			env;
	int				status;
}	t_shell;

int		shell_init(t_shell *shell, const char *name, const char **env);
void	shell_destroy(t_shell *shell);
void	shell_clear(t_shell	*shell);
void	shell_readline(t_shell *shell);

# define SHELL_BANNER "\
┌────────────────────────────────────────────────────────┐\n\
│▓▓▓▓░  ░░░▒▒▒▓▓▓███████████▓▓▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓░  ░░░▒▒▒▒░░         ░░▓▓▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓░   ░░░░       ▒▒▒▒░    ░▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓░   ░░       ░░░▒███▓   ░▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓░ ░ ░░▒▓▓▒▒▒▒▒░░░░████▒░▓▓▓▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓▒ ░ ░░░▒▓█████▓░░░░▓███▓▒▓▓▓▓▓▓▓▓▓  ╔═╗┬┌─┐┌┬┐┌─┐   │\n\
│▓▓▓▓▒ ░░░░░░▒██████▒░░░░▒████▓▓▓▓▓▓▓▓▓  ╚═╗││ ┬│││├─┤   │\n\
│▓▓▓▓▓░░░░░░░░░▓▓████▓▓▓▓▓▓▓█████▓▓▓▓▓▓  ╚═╝┴└─┘┴ ┴┴ ┴   │\n\
│▓▓▓▓▓░░▒░░░░░░░▒▒▓▓▓▒▓▒░░░      ░▓▓▓▓▓  ╔═╗┬ ┬┌─┐┬  ┬   │\n\
│▓▓▓▓▓░░▒░▒▒░░░░▒▒▒▓▓░░         ▒▓▓▓▓▓▓  ╚═╗├─┤├┤ │  │   │\n\
│▓▓▓▓▓░░▓░░▓░░░░▒▒▒▓▓▒░       ░▓▓▓▓▓▓▓▓  ╚═╝┴ ┴└─┘┴─┘┴─┘ │\n\
│▓▓▓▓▓░░▓▓▓▓░░░░░▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓▓▒░░░░░░░░░░░▒▓░░        ░▒▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓▓▓▓  ░░░░░░░░░▒▒░░▒▒▒▒▒▒░░▒▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓▓▓▒  ░░░░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓                  │\n\
│▓▓▓▓▓▓▓░   ░░░░░░░░░▒▒▒▓██████▓▒▓▓▓▓▓▓                  │\n\
└────────────────────────────────────────────────────────┘\n\
"

#endif
