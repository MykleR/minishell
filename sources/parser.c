/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:08:32 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/24 17:00:47 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <errors.h>

static t_n_terminal	get_prod(int rule)
{
	if (rule < 0 || rule >= PROD_COUNT)
		return (0);
	return (PRODUCTIONS[rule]);
}

static int	get_rhs(int rule)
{
	if (rule < 0 || rule >= PROD_COUNT)
		return (0);
	return (RHS_LENS[rule]);
}

static int	get_goto(int rule, int state)
{
	if (state < 0 || state >= STATE_COUNT
		|| rule < 0 || rule >= PROD_COUNT)
		return (0);
	return (GOTO_VALUES[state * NTERM_COUNT + get_prod(rule)]);
}

static t_action	get_action(int state, t_token_type term)
{
	uint32_t	index;

    index = state * TERM_COUNT + term;
	if (state < 0 || state >= STATE_COUNT
		|| term < 0 || term >= TERM_COUNT)
		return ((t_action){ACT_ERROR, -1});
	return ((t_action){ACTION_TYPES[index], ACTION_VALUES[index]});
}

static void	lalr_reduce(t_parser *parser, int rule)
{
	t_parse_stack	*top;

	stack_pops(&parser->stack, get_rhs(rule));
	top = stack_top(&parser->stack);
	stack_push(&parser->stack, &((t_parse_stack){
		get_goto(rule, top->state), 0}));
}

static void lalr_shift(t_parser *parser, int state)
{
	parser->token_id++;
	stack_push(&parser->stack, &((t_parse_stack){state, 0}));
}

int	lalr_parse(t_parser *parser, t_collection *tokens)
{
	t_token			*token;
	t_parse_stack	*top;
	t_action		action;

	parser->ast = NULL;
	parser->token_id = 0;
	collection_clear(&parser->stack);
    stack_push(&parser->stack, &((t_parse_stack){0, NULL}));
    while (parser->token_id < tokens->len)
	{
		token = collection_get(tokens, parser->token_id);
        top = stack_top(&parser->stack);
		action = get_action(top->state, token->type);
		//ft_printf("token:%d[%s] | state:%d | action:%d,%d\n", token->type, token->val, top->state, action.type, action.value);
		if (action.type == ACT_SHIFT)
			lalr_shift(parser, action.value);
		else if (action.type == ACT_REDUCE)
			lalr_reduce(parser, action.value);
		else if (action.type == ACT_ACCEPT)
			return (E_OK);
		else if (action.type == ACT_ERROR)
			return (E_PARSE_AST);
    }
	return (E_OK);
}
