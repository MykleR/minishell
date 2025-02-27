/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:05:01 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/27 02:00:16 by mrouves          ###   ########.fr       */
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

void ast_free(t_ast *ast)
{
	int	i;
	
	if (ast->left)
		ast_free(ast->left);
	if (ast->right)
		ast_free(ast->right);
	i = -1;
	while (++i < ast->expression.argc)
		alloc_f(ast->expression.argv[i]);
	alloc_f(ast->expression.argv);
	alloc_f(ast);
}

t_ast	*ast_from_token(t_token *token)
{
	t_ast_type	type;
	t_ast_expr	expr;

	if (token->type == T_EOF || token->type == T_LPAREN
		|| token->type == T_RPAREN)
		return (NULL);
	type = AST_CMD;
	ft_memset(&expr, 0, sizeof(t_ast_expr));
	if (token->type == T_WORD || token->type == T_IDENT
		|| token->type == T_DQUOTE || token->type == T_SQUOTE)
		expr = (t_ast_expr){.argc=1, .argv=&((char *){ft_strdup(token->val)})};
	if (token->type == T_PIPE)
		type = AST_PIPE;
	else if (token->type == T_AND)
		type = AST_AND;
	else if (token->type == T_OR)
		type = AST_OR;
	else if (token->type == T_REDIR_IN)
		type = AST_REDIR;
	else if (token->type == T_REDIR_OUT)
		type = AST_REDIR;
	else if (token->type == T_APPEND)
		type = AST_REDIR;
	return (ast_new(0, 0, type, expr));
}

void	ast_print(t_ast *ast, int depth)
{
	int	i;

	if (!ast)
		return ;
	i = -1;
	while (++i < depth)
		ft_printf("  ");
	if (ast->type == AST_CMD)
		ft_printf("CMD: %s\n", ast->expression.argv[0]);
	else if (ast->type == AST_PIPE)
		ft_printf("PIPE\n");
	else if (ast->type == AST_AND)
		ft_printf("AND\n");
	else if (ast->type == AST_OR)
		ft_printf("OR\n");
	else if (ast->type == AST_REDIR)
		ft_printf("REDIR\n");
	else
		ft_printf("UNKNOWN\n");
	if (ast->left)
		ast_print(ast->left, depth + 1);
	if (ast->right)
		ast_print(ast->right, depth + 1);
}
