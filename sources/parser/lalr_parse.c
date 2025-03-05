/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:08:32 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 01:31:13 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <errors.h>

static void	lalr_reduce(t_parser *parser, int rule)
{
	static t_ast	*rhs_nodes[0x10] = {0};
	t_parse_trace	*top;
	int				go_to;
	int				rhs_len;

	rhs_len = lalr_get_rhs(rule);
	while (rhs_len--)
		rhs_nodes[rhs_len] = ((t_parse_trace *)stack_pop(&parser->stack))->node;
	top = stack_top(&parser->stack);
	go_to = lalr_get_goto(rule, top->state);
	stack_push(&parser->stack, &((t_parse_trace){
		go_to, production(rule, rhs_nodes)}));
}

static void	lalr_shift(t_parser *parser, int state, t_collection *tokens)
{
	t_token	*token;
	t_ast	*node;

	token = collection_get(tokens, parser->token_id);
	node = ast_new(AST_TOKEN, (t_ast_expr){.token = token});
	parser->token_id++;
	stack_push(&parser->stack, &((t_parse_trace){state, node}));
}

int	lalr_parse(t_parser *parser, t_collection *tokens)
{
	t_action		action;
	t_parse_trace	*top;

	if (__builtin_expect(!parser || !tokens, 0))
		return (E_PARSE_AST);
	parser->ast = NULL;
	parser->token_id = 0;
	stack_push(&parser->stack, &((t_parse_trace){0, NULL}));
	while (parser->token_id < tokens->len)
	{
		top = stack_top(&parser->stack);
		parser->ast = top->node;
		action = lalr_get_action(top->state, ((t_token *)
					collection_get(tokens, parser->token_id))->type);
		if (action.type == ACT_SHIFT)
			lalr_shift(parser, action.value, tokens);
		else if (action.type == ACT_REDUCE)
			lalr_reduce(parser, action.value);
		else if (action.type == ACT_ACCEPT)
			return (E_OK);
		else if (action.type == ACT_ERROR)
			return (E_PARSE_AST);
	}
	return (E_PARSE_AST);
}
