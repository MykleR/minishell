/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_prods.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:41:03 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/28 01:30:27 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void add_cmd_word(t_ast *cmd_node, char *word)
{
    if (!cmd_node || cmd_node->type != AST_CMD || !word)
        return;
    char **new_args = ft_realloc(
		cmd_node->expr.cmd.argv,
		(cmd_node->expr.cmd.argc + 1) * sizeof(char *),
		cmd_node->expr.cmd.argc * sizeof(char *));
    cmd_node->expr.cmd.argv = new_args;
    cmd_node->expr.cmd.argv[cmd_node->expr.cmd.argc] = ft_strdup(word);
    cmd_node->expr.cmd.argc++;
}

static t_token *token_from_node(t_ast *node)
{
    if (!node || node->type != AST_TOKEN)
        return NULL;
    return node->expr.token;
}

t_ast *production(int rule, t_ast **node_stack)
{
    switch (rule) {
		case R_LIST_CMD_AND_LIST: // list -> ommand AND list
            return (ast_new(AST_AND, (t_ast_expr){
					.binary = {node_stack[0], node_stack[2]}}));
        case R_LIST_CMD_OR_LIST: // list -> command OR list
			return (ast_new(AST_OR, (t_ast_expr){
					.binary = {node_stack[0], node_stack[2]}}));
        case R_LIST_CMD_PIPE_LIST: // list -> command PIPE list
			return (ast_new(AST_PIPE, (t_ast_expr){
					.binary = {node_stack[0], node_stack[2]}}));
        case R_REDIR_IN: // cmd_redir -> REDIR_IN cmd_word
			return (ast_from_redir(AST_REDIR_IN, node_stack[0], node_stack[1]));
		case R_REDIR_OUT: // cmd_redir -> REDIR_OUT cmd_word
			return (ast_from_redir(AST_REDIR_OUT, node_stack[0], node_stack[1]));
		case R_REDIR_APP: // cmd_redir -> APPEND cmd_word
			return (ast_from_redir(AST_REDIR_APP, node_stack[0], node_stack[1]));
		case R_CMD_WORD:  // command -> cmd_word
        {
            t_token *token = token_from_node(node_stack[0]);
            t_ast *new_node = ast_new(AST_CMD, (t_ast_expr){.cmd = {NULL, 0}});
			add_cmd_word(new_node, (char *)token->val);
            return (new_node);
        }
        case R_CMD_WORD_REC: // command -> command cmd_word
        {
            t_ast *cmd_node = node_stack[0];
            if (cmd_node->type == AST_CMD) {
                t_token *token = token_from_node(node_stack[1]);
                if (token)
                    add_cmd_word(cmd_node, (char *)token->val);
            }
			return (cmd_node);
        }
        case R_CMD_REDIR_REC: // command -> command cmd_redir
        {
            t_ast *new_node = node_stack[0];
            t_ast *cmd_node = node_stack[1];
            if (new_node->type == AST_REDIR_IN ||
                new_node->type == AST_REDIR_OUT ||
                new_node->type == AST_REDIR_APP) {
                new_node->expr.redir.next = cmd_node;
            }
			return (new_node);
        }
		case R_SUBSHELL_LIST: // subshell -> LBRACKET list RBRACKET
            return(ast_new(AST_SUBSHELL, (t_ast_expr){.binary = {node_stack[1], NULL}}));
    }
    return (node_stack[0]);
}

