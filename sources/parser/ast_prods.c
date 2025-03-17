/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_prods.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:41:03 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/17 18:42:25 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

// Find the last redirection node in a chain
static t_ast	*find_last_redir(t_ast *node)
{
	while (ast_is_redir(node->expr.redir.next))
		node = node->expr.redir.next;
	return (node);
}

// Find the command node at the end of a redirection chain
static t_ast	*find_last_command(t_ast *node)
{
	t_ast	*lcmd;

	if (!ast_is_redir(node))
		return (node);
	lcmd = find_last_redir(node)->expr.redir.next;
	if (lcmd && lcmd->type == AST_CMD)
		return (lcmd);
	return (NULL);
}

// Recursive grammar rule: cmd -> cmd WORD
static t_ast	*ast_cmd_rec(t_ast *cmd, t_ast *word)
{
	t_ast		*last;

	last = find_last_command(cmd);
	if (!last || last->type != AST_CMD)
	{
		if (ast_is_redir(cmd))
			find_last_redir(cmd)->expr.redir.next = ast_from_word(word);
		return (cmd);
	}
	collection_insert(&last->expr.cmd.args,
		&(char *){ft_strdup(word->expr.token->val)},
		last->expr.cmd.args.len - 1);
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
	if (redir)
		redir->expr.redir.next = cmd;
	return (redir);
}

t_ast	*production(int rule, t_ast **rhs)
{
	if (rule == R_LIST_OR_LIST)
		return (ast_new(AST_OR, (t_ast_expr){.binary = {rhs[0], rhs[2]}}));
	if (rule == R_LIST_AND_LIST)
		return (ast_new(AST_AND, (t_ast_expr){.binary = {rhs[0], rhs[2]}}));
	if (rule == R_LIST_PIPE_LIST)
		return (ast_new(AST_PIPE, (t_ast_expr){.binary = {rhs[0], rhs[2]}}));
	if (rule == R_LIST_SUBSHELL)
		return (ast_new(AST_SUBSHELL, (t_ast_expr){.binary = {rhs[1], NULL}}));
	if (rule == R_REDIR_IN)
		return (ast_from_redir(REDIR_IN, rhs[1]));
	if (rule == R_REDIR_OUT)
		return (ast_from_redir(REDIR_OUT, rhs[1]));
	if (rule == R_REDIR_APP)
		return (ast_from_redir(REDIR_APP, rhs[1]));
	if (rule == R_CMD_ARG)
		return (ast_from_word(rhs[0]));
	if (rule == R_CMD_ARG_REC)
		return (ast_cmd_rec(rhs[0], rhs[1]));
	if (rule == R_CMD_REDIR_REC)
		return (ast_redir_rec(rhs[0], rhs[1]));
	return (rhs[0]);
}
