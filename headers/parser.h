/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:29:18 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/18 23:41:37 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>
# include <ast.h>

# define NB_STATE	23
# define NB_NTERM	5
# define NB_TERM	10
# define NB_PROD	14

typedef enum e_grammar_rules
{
	R_PROGRAM			= 0,
	R_LIST_OR_LIST		= 1,
	R_LIST_AND_LIST		= 2,
	R_LIST_PIPE_LIST	= 3,
	R_LIST_SUBSHELL		= 4,
	R_LIST_CMD			= 5,
	R_CMD_ARG			= 6,
	R_CMD_REDIR			= 7,
	R_CMD_ARG_REC		= 8,
	R_CMD_REDIR_REC		= 9,
	R_REDIR_IN			= 10,
	R_REDIR_OUT			= 11,
	R_REDIR_APP			= 12,
	R_ARG				= 13,
}	t_grammar_rules;

typedef enum e_action_type
{
	ACT_ERROR	= 0,
	ACT_SHIFT	= 1,
	ACT_REDUCE	= 2,
	ACT_ACCEPT	= 3,
}	t_action_type;

typedef struct s_parse_trace
{
	int		state;
	t_ast	*node;
}	t_parse_trace;

typedef struct s_parse_action
{
	t_action_type	type;
	int				value;
}	t_action;

typedef struct s_parser
{
	t_ast		*ast;
	t_stack		stack;
	uint32_t	token_id;
}	t_parser;

int			lalr_parse(t_parser *parser, t_collection *tokens);
int			lalr_get_prod(int rule);
int			lalr_get_rhs(int rule);
int			lalr_get_goto(int rule, int state);
t_action	lalr_get_action(int state, t_terminal term);
t_ast		*production(int rule, t_ast **rhs_nodes);

# define PRODUCTIONS	"\x0\x1\x1\x1\x1\x1\x2\x2\x2\x2\x3\x3\x3\x4"
# define RHS_LENS		"\x1\x3\x3\x3\x3\x1\x1\x1\x2\x2\x2\x2\x2\x1"

# define GOTO_VALUES "\
\x00\x01\x03\x05\x04\
\x00\x00\x00\x00\x00\
\x00\x0d\x03\x05\x04\
\x00\x00\x00\x0f\x0e\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x10\
\x00\x00\x00\x00\x11\
\x00\x00\x00\x00\x12\
\x00\x13\x03\x05\x04\
\x00\x14\x03\x05\x04\
\x00\x15\x03\x05\x04\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
"

# define ACTION_VALUES	"\
\x00\x00\x00\x02\x00\x07\x08\x09\x06\x00\
\x0a\x0b\x0c\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x02\x00\x07\x08\x09\x06\x00\
\x05\x05\x05\x00\x05\x07\x08\x09\x06\x05\
\x06\x06\x06\x00\x06\x06\x06\x06\x06\x06\
\x07\x07\x07\x00\x07\x07\x07\x07\x07\x07\
\x0d\x0d\x0d\x00\x0d\x0d\x0d\x0d\x0d\x0d\
\x00\x00\x00\x00\x00\x00\x00\x00\x06\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x06\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x06\x00\
\x00\x00\x00\x02\x00\x07\x08\x09\x06\x00\
\x00\x00\x00\x02\x00\x07\x08\x09\x06\x00\
\x00\x00\x00\x02\x00\x07\x08\x09\x06\x00\
\x0a\x0b\x0c\x00\x16\x00\x00\x00\x00\x00\
\x08\x08\x08\x00\x08\x08\x08\x08\x08\x08\
\x09\x09\x09\x00\x09\x09\x09\x09\x09\x09\
\x0a\x0a\x0a\x00\x0a\x0a\x0a\x0a\x0a\x0a\
\x0b\x0b\x0b\x00\x0b\x0b\x0b\x0b\x0b\x0b\
\x0c\x0c\x0c\x00\x0c\x0c\x0c\x0c\x0c\x0c\
\x01\x01\x0c\x00\x01\x00\x00\x00\x00\x01\
\x02\x02\x0c\x00\x02\x00\x00\x00\x00\x02\
\x03\x03\x0c\x00\x03\x00\x00\x00\x00\x03\
\x04\x04\x04\x00\x04\x00\x00\x00\x00\x04\
"

# define ACTION_TYPES "\
\x00\x00\x00\x01\x00\x01\x01\x01\x01\x03\
\x01\x01\x01\x00\x00\x00\x00\x00\x00\x03\
\x00\x00\x00\x01\x00\x01\x01\x01\x01\x00\
\x02\x02\x02\x00\x02\x01\x01\x01\x01\x02\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\
\x00\x00\x00\x01\x00\x01\x01\x01\x01\x00\
\x00\x00\x00\x01\x00\x01\x01\x01\x01\x00\
\x00\x00\x00\x01\x00\x01\x01\x01\x01\x00\
\x01\x01\x01\x00\x01\x00\x00\x00\x00\x00\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\
\x02\x02\x01\x00\x02\x00\x00\x00\x00\x02\
\x02\x02\x01\x00\x02\x00\x00\x00\x00\x02\
\x02\x02\x01\x00\x02\x00\x00\x00\x00\x02\
\x02\x02\x02\x00\x02\x00\x00\x00\x00\x02\
"

#endif
