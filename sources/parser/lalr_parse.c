/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:08:32 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 16:04:57 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	lalr_reduce(t_parser *parser, int rule)
{
	static t_ast	*rhs_nodes[0x10] = {0};
	t_parse_trace	*trace;
	int				go_to;
	int				rhs_len;

	rhs_len = lalr_get_rhs(rule);
	while (rhs_len--)
	{
		trace = stack_pop(&parser->stack);
		rhs_nodes[rhs_len] = trace->node;
	}
	trace = stack_top(&parser->stack);
	go_to = lalr_get_goto(rule, trace->state);
	stack_push(&parser->stack, &((t_parse_trace){
			go_to, production(rule, rhs_nodes)}));
}

static void	lalr_shift(t_parser *parser, int state, t_token *token)
{
	t_ast	*node;

	node = ast_new(AST_TOKEN, (t_ast_expr){.token = token});
	stack_push(&parser->stack, &((t_parse_trace){state, node}));
	parser->token_id++;
}

int	lalr_parse(t_parser *parser, t_collection *tokens)
{
	t_action		action;
	t_parse_trace	*top;
	t_token			*token;

	parser->token_id = 0;
	stack_push(&parser->stack, &((t_parse_trace){0, NULL}));
	while (parser->token_id < tokens->len
		&& action.type != ACT_ERROR
		&& action.type != ACT_ACCEPT)
	{
		top = stack_top(&parser->stack);
		token = collection_get(tokens, parser->token_id);
		action = lalr_get_action(top->state, token->type);
		parser->ast = top->node;
		if (action.type == ACT_SHIFT)
			lalr_shift(parser, action.value, token);
		else if (action.type == ACT_REDUCE)
			lalr_reduce(parser, action.value);
	}
	if (action.type == ACT_ERROR)
		return (error(E_PARSE_AST, token->val));
	return (E_OK);
}
