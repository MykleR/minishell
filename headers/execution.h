/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:19:27 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/06 01:15:32 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <ast.h>

# define PATH_MAX 4096

typedef enum e_access
{
	READ,
	WRITE
}	t_access;

typedef struct s_redir
{
	int	fd;
	int	backup;
}	t_redir;

int		builtin_cd(char *path, t_hm *env);
int		builtin_echo(char **args, t_hm *env);
int		builtin_pwd(void);

int		query_child(pid_t pid);
int		redirection(int fd_to, int fd_from, t_ast *todo);

int		execute_cmd(t_cmd_expr *cmd);
int		execute_pipe(t_binary_expr *pipe);
int		execute_and(t_binary_expr *and);
int		execute_or(t_binary_expr *or);
int		execute_redir(t_redir_expr *redir);

int		evaluate(t_ast *ast);

#endif
