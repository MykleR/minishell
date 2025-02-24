/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:08:32 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/24 20:49:29 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <errors.h>

static void	lalr_reduce(t_parser *parser, int rule)
{
	t_parse_trace	*top;
	int				goto_state;

	stack_pops(&parser->stack, lalr_get_rhs(rule));
	top = stack_top(&parser->stack);
	goto_state = lalr_get_goto(rule, top->state);
	stack_push(&parser->stack, &((t_parse_trace){goto_state, 0}));
}

static void	lalr_shift(t_parser *parser, int state)
{
	parser->token_id++;
	stack_push(&parser->stack, &((t_parse_trace){state, 0}));
}

int	lalr_parse(t_parser *parser, t_collection *tokens)
{
	t_action		action;

	if (__builtin_expect(!parser || !tokens, 0))
		return (E_PARSE_AST);
	parser->ast = NULL;
	parser->token_id = 0;
	stack_push(&parser->stack, &((t_parse_trace){0, NULL}));
	while (parser->token_id < tokens->len)
	{
		action = lalr_get_action(
				((t_parse_trace *)stack_top(&parser->stack))->state,
				((t_token *)collection_get(tokens, parser->token_id))->type);
		if (action.type == ACT_SHIFT)
			lalr_shift(parser, action.value);
		else if (action.type == ACT_REDUCE)
			lalr_reduce(parser, action.value);
		else if (action.type == ACT_ACCEPT)
			return (E_OK);
		else if (action.type == ACT_ERROR)
			return (E_PARSE_AST);
	}
	return (E_PARSE_AST);
}
