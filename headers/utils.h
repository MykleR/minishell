/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:00:07 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 16:32:56 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

# define E_MSG_ERROR "%s: %s\n\0"
# define E_MSG_OK "OK.\n\0"
# define E_MSG_LEX "syntax error near unexpected token '%s'\n\0"
# define E_MSG_AST "syntax error near unexpected token '%s'\n\0"
# define E_MSG_OPEN "%s: %s: %s\n\0"
# define E_MSG_TOOMANY "%s: too many arguments\n\0"
# define E_MSG_NOTCMD "Command '%s' not found\n\0"
# define E_MSG_NOTSET "%s: '%s' not set\n\0"
# define E_MSG_NUMERIC "%s: %s: numeric argument required\n\0"

typedef enum e_errors_type
{
	E_ERROR			= -1,
	E_OK			= 0,
	E_PARSE_LEX		= E_OK + sizeof(E_MSG_OK) - 1,
	E_PARSE_AST		= E_PARSE_LEX + sizeof(E_MSG_LEX) - 1,
	E_OPEN			= E_PARSE_AST + sizeof(E_MSG_AST) - 1,
	E_TOOMANY		= E_OPEN + sizeof(E_MSG_OPEN) - 1,
	E_NOTCMD		= E_TOOMANY + sizeof(E_MSG_TOOMANY) - 1,
	E_NOTSET		= E_NOTCMD + sizeof(E_MSG_NOTCMD) - 1,
	E_NUMERIC		= E_NOTSET + sizeof(E_MSG_NOTSET) - 1
}	t_error_type;

typedef enum e_sig_type
{
	SIG_IGNORE,
	SIG_RESTORE,
	SIG_SIMPLE,
	SIG_COMPLEX
}	t_sig_type;

typedef struct sigaction	t_sigaction;

typedef union u_sig_callb
{
	void		(*h_simple)(int);
	void		(*h_complex)(int, siginfo_t *, void *);
}	t_sig_callb;

int		safe_fork(void);
int		safe_open(const char *filename, int flags);
int		safe_close(int fd);
int		safe_dup2(int oldfd, int newfd);
int		safe_pipe(int pipefd[2]);

int		env_init(t_hmap *env, const char **envp);

int		sig_handle(int num, t_sig_callb handler, t_sig_type type);

int		error(t_error_type e, ...);

#endif
