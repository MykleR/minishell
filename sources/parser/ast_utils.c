/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:05:01 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/28 01:29:40 by mrouves          ###   ########.fr       */
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

t_ast	*ast_from_token(t_token *token)
{
	return (ast_new(AST_TOKEN, (t_ast_expr){.token = token}));
}

t_ast	*ast_from_redir(t_ast_type type, t_ast *prev, t_ast *word)
{
	t_token		*token;
	t_ast_expr	expr;

	(void) prev;
	token = NULL;
	expr = (t_ast_expr){.redir = {NULL, NULL, -1}};
	if (word && word->type == AST_TOKEN)
		token = word->expr.token;
	if (token)
		expr.redir.file = ft_strdup(token->val);
	return (ast_new(type, expr));
}
