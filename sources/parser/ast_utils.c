/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:05:01 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/04 00:12:42 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

t_ast	*ast_new(t_ast_type type, t_ast_expr expr)
{
	t_ast	*node;

	node = ft_calloc(sizeof(t_ast), 1);
	node->type = type;
	node->expr = expr;
	return (node);
}

/*
** This function creates a temporary TOKEN AST node
*/
t_ast	*ast_from_token(t_token *token)
{
	return (ast_new(AST_TOKEN, (t_ast_expr){.token = token}));
}

/*
** This function creates a CMD AST node
*/
t_ast	*ast_from_word(t_ast *word)
{
	char	**argv;

	argv = alloc_m(sizeof(char *) * 2);
	argv[0] = ft_strdup(word->expr.token->val);
	argv[1] = NULL;
	return (ast_new(AST_CMD, (t_ast_expr){.cmd = {argv, 1}}));
}

/*
** This function creates a redirection AST node
*/
t_ast	*ast_from_redir(t_redir_type type, t_ast *word)
{
	t_ast_expr	expr;

	expr = (t_ast_expr){.redir = {NULL, NULL, -1, type}};
	if (word && word->type == AST_TOKEN)
		expr.redir.file = ft_strdup(word->expr.token->val);
	return (ast_new(AST_REDIR, expr));
}

bool	ast_is_redir(t_ast *ast)
{
	return (ast && (ast->type == AST_REDIR));
}
