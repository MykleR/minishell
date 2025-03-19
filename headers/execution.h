/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:19:27 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/19 05:35:59 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <ast.h>

# define PATH_MAX 4096
# define NB_BUILTINS 7

typedef enum e_access
{
	READ	= 0,
	WRITE	= 1
}	t_access;

typedef int	(*t_builtin)(const char **args, int argc, t_hmap *env);

typedef struct s_match_builtin
{
	const char	*name;
	t_builtin	func;
}	t_match_builtin;

int		evaluate(t_ast *ast, t_hmap *env);

int		exec_path(const char **args,		t_hmap *env);
int		execute_cmd(t_cmd_expr *cmd,		t_hmap *env);
int		execute_pipe(t_binary_expr *pipe,	t_hmap *env);
int		execute_and(t_binary_expr *and,		t_hmap *env);
int		execute_or(t_binary_expr *or,		t_hmap *env);
int		execute_redir(t_redir_expr *redir,	t_hmap *env);
int		execute_subshell(t_binary_expr *expr, t_hmap *env);

int		builtin_cd(const char **args, int argc, t_hmap *env);
int		builtin_pwd(const char **args, int argc, t_hmap *env);
int		builtin_env(const char **args, int argc, t_hmap *env);
int		builtin_exit(const char **args, int argc, t_hmap *env);
int		builtin_echo(const char **args,	int argc, t_hmap *env);
int		builtin_unset(const char **args, int argc, t_hmap *env);
int		builtin_export(const char **args, int argc, t_hmap *env);

int		query_child(pid_t pid);
int		redirection(int fd_to, int fd_from, t_ast *todo, t_hmap *env);

#endif
