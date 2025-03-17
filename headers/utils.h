/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:00:07 by mykle             #+#    #+#             */
/*   Updated: 2025/03/17 04:34:03 by mykle            ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define E_MSG_ERROR "%s: %s\n\0"
# define E_MSG_OK "OK.\n\0"
# define E_MSG_LEX "syntax error near unexpected token '%s'\n\0"
# define E_MSG_AST "syntax error near unexpected token '%s'\n\0"
# define E_MSG_OPEN "%s: %s: %s\n\0"
# define E_MSG_TOOMANY "%s: too many arguments\n\0"
# define E_MSG_NOTCMD "Command '%s' not found\n\0"
# define E_MSG_NOTSET "%s: '%s' not set\n\0"
# define E_MSG_NUMERIC "%s: %s: numeric argument required\n\0"
# define E_MSG_IDENTIF "%s: '%s': not a valid identifier\n\0"
# define E_MSG_ISDIR "%s: Is a directory\n\0"
# define E_MSG_HDEOF "warning: here-document at line %s \
delimited by end-of-file (wanted `%s')\n\0"

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
	E_NUMERIC		= E_NOTSET + sizeof(E_MSG_NOTSET) - 1,
	E_IDENTIF		= E_NUMERIC + sizeof(E_MSG_NUMERIC) - 1,
	E_ISDIR			= E_IDENTIF + sizeof(E_MSG_IDENTIF) - 1,
	E_HDEOF			= E_ISDIR + sizeof(E_MSG_ISDIR) - 1
}	t_error_type;

int		error(t_error_type e, ...);

int		heredoc_parse(t_collection *tokens);

char	*replace_vars(const char *str, t_hmap *env);

int		sig_set(void);
int		sig_default(void);
int		sig_ignore(void);
int		sig_exit(void);

int		safe_fork(void);
int		safe_open(const char *filename, int flags);
int		safe_close(int fd);
int		safe_dup2(int oldfd, int newfd);
int		safe_pipe(int pipefd[2]);

void	__env_print_ex(t_hmap_bucket *bucket, void *arg);
void	__env_print_ev(t_hmap_bucket *bucket, void *arg);
int		env_init(t_hmap *env, const char **envp);
char	**env_to_array(t_hmap *env);

#endif
