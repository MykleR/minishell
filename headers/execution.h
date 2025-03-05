/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:19:27 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 22:04:19 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <ast.h>

# define F_READ O_RDONLY
# define F_APPEND (O_WRONLY | O_CREAT | O_APPEND)
# define F_WRITE (O_WRONLY | O_CREAT | O_TRUNC)

typedef enum e_access { READ, WRITE } t_access;

typedef struct s_redir
{
	int	fd;
	int	backup;
}	t_redir;

int		query_child(pid_t pid);
int		redirection(int fd_to, int fd_from, t_ast *todo);

int		execute_cmd(t_cmd_expr *cmd);
int		execute_pipe(t_binary_expr *pipe);
int		execute_and(t_binary_expr *and);
int		execute_or(t_binary_expr *or);
int		execute_redir(t_redir_expr *redir);

int		evaluate(t_ast *ast);

#endif
