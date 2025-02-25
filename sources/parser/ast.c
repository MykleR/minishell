/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:05:01 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/25 14:09:32 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

t_ast	*ast_new(t_ast *l, t_ast *r, t_ast_type type, t_ast_expr expr)
{
	t_ast	*node;

	node = alloc_m(sizeof(t_ast));
	node->left = l;
	node->right = r;
	node->type = type;
	node->expression = expr;
	return (node);
}

t_ast	*ast_cmd(char *word)
{
	char	**argv;

	argv = alloc_m(sizeof(char *));
	argv[0] = word;
	return (ast_new(NULL, NULL, AST_CMD, (t_ast_expr){.argc=1, .argv=argv}));
}
