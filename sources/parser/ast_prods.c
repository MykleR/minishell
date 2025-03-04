/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_prods.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:41:03 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/04 00:16:16 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

// Find the last redirection node in a chain
static t_ast	*find_last_redir(t_ast *redir)
{
	if (!redir || !ast_is_redir(redir))
		return (NULL);
	while (ast_is_redir(redir->expr.redir.next))
		redir = redir->expr.redir.next;
	return (redir);
}

// Find the command node at the end of a redirection chain
static t_ast	*find_last_command(t_ast *redir)
{
	t_ast	*last;

	last = find_last_redir(redir);
	if (!last || !last->expr.redir.next
		|| last->expr.redir.next->type != AST_CMD)
		return (NULL);
	return (last->expr.redir.next);
}

// Recursive grammar rule: cmd -> cmd WORD
static t_ast	*ast_cmd_rec(t_ast *cmd, t_ast *word)
{
	t_cmd_expr	*expr;

	expr = &cmd->expr.cmd;
	if (ast_is_redir(cmd))
	{
		if (!find_last_command(cmd))
		{
			find_last_redir(cmd)->expr.redir.next = ast_from_word(word);
			return (cmd);
		}
		expr = &(find_last_command(cmd))->expr.cmd;
	}
	expr->argv = ft_realloc(expr->argv,
			sizeof(char *) * (expr->argc + 2),
			sizeof(char *) * expr->argc);
	expr->argv[expr->argc++] = ft_strdup(word->expr.token->val);
	expr->argv[expr->argc] = NULL;
	return (cmd);
}

//Recursive grammar rule: cmd -> cmd redir
static t_ast	*ast_redir_rec(t_ast *cmd, t_ast *redir)
{
	t_ast	*last;

	if (ast_is_redir(cmd))
	{
		last = find_last_redir(cmd);
		redir->expr.redir.next = last->expr.redir.next;
		last->expr.redir.next = redir;
		return (cmd);
	}
	redir->expr.redir.next = cmd;
	return (redir);
}

t_ast	*production(int rule, t_ast **rhs)
{
	if (rule == R_LIST_CMD_AND_LIST)
		return (ast_new(AST_AND, (t_ast_expr){.binary = {rhs[0], rhs[2]}}));
	if (rule == R_LIST_CMD_OR_LIST)
		return (ast_new(AST_OR, (t_ast_expr){.binary = {rhs[0], rhs[2]}}));
	if (rule == R_LIST_CMD_PIPE_LIST)
		return (ast_new(AST_PIPE, (t_ast_expr){.binary = {rhs[0], rhs[2]}}));
	if (rule == R_CMD_SUBSHELL)
		return (ast_new(AST_SUBSHELL, (t_ast_expr){.binary = {rhs[0], NULL}}));
	if (rule == R_REDIR_IN)
		return (ast_from_redir(REDIR_IN, rhs[1]));
	if (rule == R_REDIR_OUT)
		return (ast_from_redir(REDIR_OUT, rhs[1]));
	if (rule == R_REDIR_APP)
		return (ast_from_redir(REDIR_APP, rhs[1]));
	if (rule == R_CMD_WORD)
		return (ast_from_word(rhs[0]));
	if (rule == R_CMD_WORD_REC)
		return (ast_cmd_rec(rhs[0], rhs[1]));
	if (rule == R_CMD_REDIR_REC)
		return (ast_redir_rec(rhs[0], rhs[1]));
	if (rule == R_SUBSHELL_LIST)
		return (rhs[1]);
	return (rhs[0]);
}
