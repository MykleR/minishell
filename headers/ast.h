/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:59:31 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/25 13:10:00 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <libft.h>

typedef enum e_ast_type
{
	AST_CMD		= 0,
	AST_PIPE	= 1,
	AST_AND		= 2,
	AST_OR		= 3,
	AST_REDIR	= 4,
}	t_ast_type;

typedef enum e_ast_redir
{
	AST_OUT	= 0,
	AST_IN	= 1,
	AST_APP	= 2,
}	t_ast_redir;

typedef union u_ast_expression
{
	struct
	{
		char	**argv;
		int		argc;
	};
	struct
	{
		char		*file;
		int			fd;
		t_ast_redir	redir;
	};
}	t_ast_expr;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_ast_type		type;
	t_ast_expr		expression;
}	t_ast;

t_ast	*ast_new(t_ast *l, t_ast *r, t_ast_type type, t_ast_expr expr);

#endif
