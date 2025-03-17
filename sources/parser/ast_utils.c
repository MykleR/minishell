/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:05:01 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/17 21:16:44 by mykle            ###   ########.fr       */
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
** This function creates a CMD AST node
*/
t_ast	*ast_from_word(t_ast *word)
{
	const t_clear_info	clear = {alloc_f, T_HEAP};
	t_cmd_expr			cmd;

	if (!word || word->type != AST_TOKEN)
		return (NULL);
	collection_init(&cmd.args, sizeof(char *), 8, clear);
	collection_append(&cmd.args, &(char *){ft_strdup(word->expr.token->val)});
	collection_append(&cmd.args, &(char *){NULL});
	return (ast_new(AST_CMD, (t_ast_expr){.cmd = cmd}));
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

void	ast_free(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == AST_PIPE || ast->type == AST_AND || ast->type == AST_OR)
	{
		ast_free(ast->expr.binary.left);
		ast_free(ast->expr.binary.right);
	}
	if (ast->type == AST_CMD)
		collection_clear(&ast->expr.cmd.args);
	if (ast->type == AST_REDIR)
	{
		ast_free(ast->expr.redir.next);
		alloc_f(ast->expr.redir.file);
	}
	alloc_f(ast);
}
