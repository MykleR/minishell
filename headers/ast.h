/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:59:31 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 17:10:27 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <lexer.h>

typedef enum e_ast_type
{
	AST_TOKEN		= -1,
	AST_CMD			= 0,
	AST_PIPE		= 1,
	AST_AND			= 2,
	AST_OR			= 3,
	AST_REDIR		= 4,
	AST_SUBSHELL	= 5,
}	t_ast_type;

typedef enum e_redir_type
{
	REDIR_IN	= 0,
	REDIR_OUT	= 1,
	REDIR_APP	= 2,
}	t_redir_type;

typedef struct s_ast	t_ast;

typedef struct s_binary_expr
{
	t_ast	*left;
	t_ast	*right;
}	t_binary_expr;

typedef struct s_redir_expr
{
	t_ast			*next;
	char			*file;
	int				fd;
	t_redir_type	type;
}	t_redir_expr;

typedef struct s_cmd_expr
{
	char	**argv;
	int		argc;
}	t_cmd_expr;

typedef union u_ast_expr
{
	t_binary_expr	binary;
	t_cmd_expr		cmd;
	t_redir_expr	redir;
	t_token			*token; // For temporary token nodes
}	t_ast_expr;

struct s_ast
{
	t_ast_type	type;
	t_ast_expr	expr;
};

t_ast	*ast_new(t_ast_type type, t_ast_expr expr);
t_ast	*ast_from_word(t_ast *word);
t_ast	*ast_from_redir(t_redir_type type, t_ast *word);
bool	ast_is_redir(t_ast *ast);
void	ast_print(t_ast *ast);

#endif
