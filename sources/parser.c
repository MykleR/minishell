/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:08:32 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/21 17:30:28 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <errors.h>

static t_action get_action(int state, t_token_type terminal)
{

    if (state < 0 || state >= S_COUNT || terminal < 0 || terminal > T_COUNT)
        return (t_action){ACT_ERROR, -1};
    return ((char *)ACTION_TABLE) + state * T_COUNT + terminal;
}

/*
if token.type is T_WORD, T_IDENT, T_SQUOTE, T_DQUOTE:
        node = create_ast_node(AST_CMD)
        node.expression.argv = [token.val]
        node.expression.argc = 1
        return node
*/
static t_ast_node	*create_leaf(t_token *token)
{
	t_ast_node	*node;

	if (token->type != T_WORD && token->type != T_IDENT
		&& token->type != T_SQUOTE && token->type != T_DQUOTE)
		return (NULL);
	node = alloc_m(sizeof(t_ast_node));
	node->type = AST_CMD;
	node->expression.argv[0] = (char *)(token->val);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// TODO
static void production(void)
{

}

// TODO
static void	lalr_reduce(t_parser *parser, t_action action)
{
	(void) parser;
	(void) action;
	(void) production;
}

static void lalr_shift(t_parser *parser, t_token *token, t_action action)
{
	parser->token_id++;
	stack_push(&parser->stack, &((t_parse_stack){
		action.value, create_leaf(token)}));
}

int	lalr_parse(t_parser *parser, t_collection *tokens)
{
	t_token		*token;
	t_action	action;
	int			state;

	parser->ast = NULL;
	parser->token_id = 0;
	collection_clear(&parser->stack);
    stack_push(&parser->stack, &((t_parse_stack){0, NULL}));
    while (parser->token_id < tokens->len)
	{
		token = collection_get(tokens, parser->token_id);
        state = ((t_parse_stack *)stack_top(&parser->stack))->state;
		action = get_action(state, token->type);
		if (action.type == ACT_SHIFT)
			lalr_shift(parser, token, action);
		else if (action.type == ACT_REDUCE)
			lalr_reduce(parser, action);
		else if (action.type == ACT_ACCEPT)
			return (E_OK);
		else if (action.type == ACT_ERROR)
			return (E_PARSE_AST);
    }
	return (E_PARSE_AST);
}
