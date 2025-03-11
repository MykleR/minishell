/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:25:55 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/11 22:45:31 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdio.h>

static char	*get_ast_type_str(t_ast_type type)
{
	if (type == AST_TOKEN)
		return ("TOKEN");
	else if (type == AST_AND)
		return ("AND");
	else if (type == AST_OR)
		return ("OR");
	else if (type == AST_PIPE)
		return ("PIPE");
	else if (type == AST_REDIR)
		return ("REDIR");
	else if (type == AST_CMD)
		return ("CMD");
	else if (type == AST_SUBSHELL)
		return ("SUBSHELL");
	else
		return ("UNKNOWN");
}

static void	print_cmd_args(t_cmd_expr *cmd, int indent)
{
	int	i;

	i = -1;
	while (++i < cmd->argc)
		printf("%*s└─ ARG[%d]: '%s'\n", indent + 2, "", i, cmd->argv[i]);
}

static void	print_node_info(t_ast *node)
{
	if (node->type == AST_TOKEN && node->expr.token)
		printf(" ('%s')", node->expr.token->val);
	else if (node->type == AST_CMD && node->expr.cmd.argc > 0)
		printf(" [%s]", node->expr.cmd.argv[0]);
	else if (node->type == AST_REDIR && node->expr.redir.file)
	{
		if (node->expr.redir.type == REDIR_IN)
			printf(" -> REDIR_IN:'%s'", node->expr.redir.file);
		else if (node->expr.redir.type == REDIR_OUT)
			printf(" -> REDIR_OUT:'%s'", node->expr.redir.file);
		else if (node->expr.redir.type == REDIR_APP)
			printf(" -> REDIR_APP:'%s'", node->expr.redir.file);
	}
	printf("\n");
}

static void	ast_print_recursive(t_ast *node, int indent)
{
	char	*type_str;

	if (!node)
		return ;
	type_str = get_ast_type_str(node->type);
	printf("\x1b[34m%*s%s\x1b[0m", indent, "", type_str);
	print_node_info(node);
	if (node->type == AST_AND || node->type == AST_OR || node->type == AST_PIPE)
	{
		printf("%*s└─ LEFT:\n", indent + 2, "");
		ast_print_recursive(node->expr.binary.left, indent + 4);
		printf("%*s└─ RIGHT:\n", indent + 2, "");
		ast_print_recursive(node->expr.binary.right, indent + 4);
	}
	else if (node->type == AST_REDIR && node->expr.redir.next)
		ast_print_recursive(node->expr.redir.next, indent + 4);
	else if (node->type == AST_CMD)
		print_cmd_args(&node->expr.cmd, indent);
	else if (node->type == AST_SUBSHELL)
		ast_print_recursive(node->expr.binary.left, indent + 4);
}

/**
 * Public function to print the AST
 */
void	ast_print(t_ast *root)
{
	if (!root)
		printf("\x1b[34m\x1b[31mEmpty AST (NULL)\x1b[0m\n");
	else
		ast_print_recursive(root, 0);
}
