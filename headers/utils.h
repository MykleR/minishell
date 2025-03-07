/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:00:07 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 03:39:19 by mykle            ###   ########.fr       */
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

# define NB_ERRORS 10

# define E_MSG_OK "OK.\n\0"
# define E_MSG_LEX "syntax error near unexpected token '%s'\n\0"
# define E_MSG_AST "syntax error near unexpected token '%s'\n\0"
# define E_MSG_IS_DIR "Is a directory\n\0"
# define E_MSG_NOFILE "No such file or directory\n\0"
# define E_MSG_OPEN "%s: %s: %s\n\0"
# define E_MSG_TOO_MANY "%s: too many arguments\n\0"
# define E_MSG_NOCMD "Command '%s' not found\n\0"
# define E_MSG_NOENV "%s: '%s' not set\n\0"
# define E_MSG_NUMERIC "%s: %s: numeric argument required\n\0"

typedef enum e_errors_type
{
	E_ERROR			= -1,
	E_OK			= 0,
	E_PARSE_LEX		= E_OK + sizeof(E_MSG_OK) - 1,
	E_PARSE_AST		= E_PARSE_LEX + sizeof(E_MSG_LEX) - 1,
	E_IS_DIR		= E_PARSE_AST + sizeof(E_MSG_AST) - 1,
	E_NOFILE		= E_IS_DIR + sizeof(E_MSG_IS_DIR) - 1,
	E_OPEN			= E_NOFILE + sizeof(E_MSG_NOFILE) - 1,
	E_TOO_MANY		= E_OPEN + sizeof(E_MSG_OPEN) - 1,
	E_NOCMD			= E_TOO_MANY + sizeof(E_MSG_TOO_MANY) - 1,
	E_NOENV			= E_NOCMD + sizeof(E_MSG_NOCMD) - 1,
	E_NUMERIC		= E_NOENV + sizeof(E_MSG_NOENV) - 1
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
