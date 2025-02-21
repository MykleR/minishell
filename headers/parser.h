/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:29:18 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/21 02:17:03 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>

# define S_COUNT	28
# define T_COUNT	13
# define NT_COUNT	 7

// terminals are lexer tokens so no need to redefine them
// thos are non terminals:
typedef enum e_n_terminals
{
	NT_PROGRAM,
	NT_LIST,
	NT_PIPELINE,
	NT_CMD_REDIR,
	NT_CMD_WORD,
	NT_CMD,
	NT_SUBSHELL,
}	t_n_terminals;

typedef enum e_action_type
{
    ACT_ERROR,
    ACT_SHIFT,
    ACT_REDUCE,
    ACT_ACCEPT,
} t_action_type;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_REDIR,
}	t_ast_type;

typedef enum e_ast_redir
{
	AST_OUT,
	AST_IN,
	AST_APP,
}	t_ast_redir;

typedef union u_ast_expression
{
	struct
	{
		char	**argv;
		int		argc;
	};
	struct
	{
		char		*file;
		t_ast_redir redir;
		int			fd;
	};
}	t_ast_expression;

typedef struct s_ast_node
{
	t_ast_type			type;
	t_ast_expression	expression;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_parser
{
	t_ast_node	*ast;
	t_stack		stack;
	uint32_t	token_id;
}	t_parser;

typedef struct s_parse_stack
{
    int					state;
    t_ast_node			*node;   // AST node for semantic actions
}	t_parse_stack;

typedef struct
{
	t_action_type	type;
	int				value;
}	t_action;

int	lalr_parse(t_parser *parser, t_collection *tokens);

// NOT NORMED ONLY PURPOSE IS PROTOTYPING
int goto_table[S_COUNT][NT_COUNT] = {
    {
        [NT_LIST] = 1,
        [NT_PIPELINE] = 2,
        [NT_CMD_REDIR] = 5,
        [NT_CMD_WORD] = 4,
        [NT_CMD] = 3,
        [NT_SUBSHELL] = 6,
    },
	{
        [NT_CMD_REDIR] = 19,
        [NT_CMD_WORD] = 18,
    },
	{[NT_CMD_WORD] = 20},
	{[NT_CMD_WORD] = 21},
	{[NT_CMD_WORD] = 22},
	{
        [NT_LIST] = 23,
        [NT_PIPELINE] = 2,
        [NT_CMD_REDIR] = 5,
        [NT_CMD_WORD] = 4,
        [NT_CMD] = 3,
        [NT_SUBSHELL] = 6
    },
	{
        [NT_PIPELINE] = 24,
        [NT_CMD_REDIR] = 5,
        [NT_CMD_WORD] = 4,
        [NT_CMD] = 3,
        [NT_SUBSHELL] = 6
    },
	{
        [NT_PIPELINE] = 25,
        [NT_CMD_REDIR] = 5,
        [NT_CMD_WORD] = 4,
        [NT_CMD] = 3,
        [NT_SUBSHELL] = 6
    },
	{
        [NT_CMD_REDIR] = 5,
        [NT_CMD_WORD] = 4,
        [NT_CMD] = 26,
        [NT_SUBSHELL] = 6
    },
	{
		[NT_CMD_REDIR] = 19,
		[NT_CMD_WORD] = 18
	},
};

t_action action_table[S_COUNT][T_COUNT] = {
	{
		[T_WORD] = {ACT_SHIFT, 7},
		[T_REDIR_IN] = {ACT_SHIFT, 11},
		[T_REDIR_OUT] = {ACT_SHIFT, 12},
		[T_APPEND] = {ACT_SHIFT, 13},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
		[T_LPAREN] = {ACT_SHIFT, 14},
    },
	{
		[T_AND] = {ACT_SHIFT, 15},
		[T_OR] = {ACT_SHIFT, 16},
		[T_EOF] = {ACT_ACCEPT, 0}
	},
	{
		[T_AND] = {ACT_REDUCE, 3},
		[T_OR] = {ACT_REDUCE, 3},
		[T_PIPE] = {ACT_SHIFT,17},
		[T_RPAREN] = {ACT_REDUCE, 3},
		[T_EOF] = {ACT_REDUCE, 3}
	},
	{
		[T_AND] = {ACT_REDUCE, 5},
		[T_OR] = {ACT_REDUCE, 5},
		[T_PIPE] = {ACT_REDUCE, 5},
		[T_REDIR_IN] = {ACT_SHIFT, 11},
		[T_REDIR_OUT] = {ACT_SHIFT, 12},
		[T_APPEND] = {ACT_SHIFT, 13},
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
		[T_RPAREN] = {ACT_REDUCE, 5},
		[T_EOF] = {ACT_REDUCE, 5}
	},
	{
		[T_AND] = {ACT_REDUCE, 13},
		[T_OR] = {ACT_REDUCE, 13},
		[T_PIPE] = {ACT_REDUCE, 13},
		[T_REDIR_IN] = {ACT_REDUCE, 13},
		[T_REDIR_OUT] = {ACT_REDUCE, 13},
		[T_APPEND] = {ACT_REDUCE, 13},
		[T_WORD] = {ACT_REDUCE, 13},
		[T_IDENT] = {ACT_REDUCE, 13},
		[T_DQUOTE] = {ACT_REDUCE, 13},
		[T_SQUOTE] = {ACT_REDUCE, 13},
		[T_RPAREN] = {ACT_REDUCE, 13},
		[T_EOF] = {ACT_REDUCE, 13}
	},
	{
		[T_AND] = {ACT_REDUCE, 14},
		[T_OR] = {ACT_REDUCE, 14},
		[T_PIPE] = {ACT_REDUCE, 14},
		[T_REDIR_IN] = {ACT_REDUCE, 14},
		[T_REDIR_OUT] = {ACT_REDUCE, 14},
		[T_APPEND] = {ACT_REDUCE, 14},
		[T_WORD] = {ACT_REDUCE, 14},
		[T_IDENT] = {ACT_REDUCE, 14},
		[T_DQUOTE] = {ACT_REDUCE, 14},
		[T_SQUOTE] = {ACT_REDUCE, 14},
		[T_RPAREN] = {ACT_REDUCE, 14},
		[T_EOF] = {ACT_REDUCE, 14}
	},
	{
		[T_AND] = {ACT_REDUCE, 17},
		[T_OR] = {ACT_REDUCE, 17},
		[T_PIPE] = {ACT_REDUCE, 17},
		[T_REDIR_IN] = {ACT_REDUCE, 17},
		[T_REDIR_OUT] = {ACT_REDUCE, 17},
		[T_APPEND] = {ACT_REDUCE, 17},
		[T_WORD] = {ACT_REDUCE, 17},
		[T_IDENT] = {ACT_REDUCE, 17},
		[T_DQUOTE] = {ACT_REDUCE, 17},
		[T_SQUOTE] = {ACT_REDUCE, 17},
		[T_RPAREN] = {ACT_REDUCE, 17},
		[T_EOF] = {ACT_REDUCE, 17}
	},
	{
		[T_AND] = {ACT_REDUCE, 9},
		[T_OR] = {ACT_REDUCE, 9},
		[T_PIPE] = {ACT_REDUCE, 9},
		[T_REDIR_IN] = {ACT_REDUCE, 9},
		[T_REDIR_OUT] = {ACT_REDUCE, 9},
		[T_APPEND] = {ACT_REDUCE, 9},
		[T_WORD] = {ACT_REDUCE, 9},
		[T_IDENT] = {ACT_REDUCE, 9},
		[T_DQUOTE] = {ACT_REDUCE, 9},
		[T_SQUOTE] = {ACT_REDUCE, 9},
		[T_RPAREN] = {ACT_REDUCE, 9},
		[T_EOF] = {ACT_REDUCE, 9}
	},
	{
		[T_AND] = {ACT_REDUCE, 10},
		[T_OR] = {ACT_REDUCE, 10},
		[T_PIPE] = {ACT_REDUCE, 10},
		[T_REDIR_IN] = {ACT_REDUCE, 10},
		[T_REDIR_OUT] = {ACT_REDUCE, 10},
		[T_APPEND] = {ACT_REDUCE, 10},
		[T_WORD] = {ACT_REDUCE, 10},
		[T_IDENT] = {ACT_REDUCE, 10},
		[T_DQUOTE] = {ACT_REDUCE, 10},
		[T_SQUOTE] = {ACT_REDUCE, 10},
		[T_RPAREN] = {ACT_REDUCE, 10},
		[T_EOF] = {ACT_REDUCE, 10}
	},
	{
		[T_AND] = {ACT_REDUCE, 11},
		[T_OR] = {ACT_REDUCE, 11},
		[T_PIPE] = {ACT_REDUCE, 11},
		[T_REDIR_IN] = {ACT_REDUCE, 11},
		[T_REDIR_OUT] = {ACT_REDUCE, 11},
		[T_APPEND] = {ACT_REDUCE, 11},
		[T_WORD] = {ACT_REDUCE, 11},
		[T_IDENT] = {ACT_REDUCE, 11},
		[T_DQUOTE] = {ACT_REDUCE, 11},
		[T_SQUOTE] = {ACT_REDUCE, 11},
		[T_RPAREN] = {ACT_REDUCE, 11},
		[T_EOF] = {ACT_REDUCE, 11}
	},
	{
		[T_AND] = {ACT_REDUCE, 12},
		[T_OR] = {ACT_REDUCE, 12},
		[T_PIPE] = {ACT_REDUCE, 12},
		[T_REDIR_IN] = {ACT_REDUCE, 12},
		[T_REDIR_OUT] = {ACT_REDUCE, 12},
		[T_APPEND] = {ACT_REDUCE, 12},
		[T_WORD] = {ACT_REDUCE, 12},
		[T_IDENT] = {ACT_REDUCE, 12},
		[T_DQUOTE] = {ACT_REDUCE, 12},
		[T_SQUOTE] = {ACT_REDUCE, 12},
		[T_RPAREN] = {ACT_REDUCE, 12},
		[T_EOF] = {ACT_REDUCE, 12}
	},
	{
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
	},
	{
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
	},
	{
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
	},
	{
		[T_REDIR_IN] = {ACT_SHIFT, 11},
		[T_REDIR_OUT] = {ACT_SHIFT, 12},
		[T_APPEND] = {ACT_SHIFT, 13},
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
		[T_LPAREN] = {ACT_SHIFT, 14},
	},
	{
		[T_REDIR_IN] = {ACT_SHIFT, 11},
		[T_REDIR_OUT] = {ACT_SHIFT, 12},
		[T_APPEND] = {ACT_SHIFT, 13},
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
		[T_LPAREN] = {ACT_SHIFT, 14},
	},
	{
		[T_REDIR_IN] = {ACT_SHIFT, 11},
		[T_REDIR_OUT] = {ACT_SHIFT, 12},
		[T_APPEND] = {ACT_SHIFT, 13},
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
		[T_LPAREN] = {ACT_SHIFT, 14},
	},
	{
		[T_REDIR_IN] = {ACT_SHIFT, 11},
		[T_REDIR_OUT] = {ACT_SHIFT, 12},
		[T_APPEND] = {ACT_SHIFT, 13},
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
		[T_LPAREN] = {ACT_SHIFT, 14},
	},
	{
		[T_AND] = {ACT_REDUCE, 15},
		[T_OR] = {ACT_REDUCE, 15},
		[T_PIPE] = {ACT_REDUCE, 15},
		[T_REDIR_IN] = {ACT_REDUCE, 15},
		[T_REDIR_OUT] = {ACT_REDUCE, 15},
		[T_APPEND] = {ACT_REDUCE, 15},
		[T_WORD] = {ACT_REDUCE, 15},
		[T_IDENT] = {ACT_REDUCE, 15},
		[T_DQUOTE] = {ACT_REDUCE, 15},
		[T_SQUOTE] = {ACT_REDUCE, 15},
		[T_RPAREN] = {ACT_REDUCE, 15},
		[T_EOF] = {ACT_REDUCE, 15}
	},
	{
		[T_AND] = {ACT_REDUCE, 16},
		[T_OR] = {ACT_REDUCE, 16},
		[T_PIPE] = {ACT_REDUCE, 16},
		[T_REDIR_IN] = {ACT_REDUCE, 16},
		[T_REDIR_OUT] = {ACT_REDUCE, 16},
		[T_APPEND] = {ACT_REDUCE, 16},
		[T_WORD] = {ACT_REDUCE, 16},
		[T_IDENT] = {ACT_REDUCE, 16},
		[T_DQUOTE] = {ACT_REDUCE, 16},
		[T_SQUOTE] = {ACT_REDUCE, 16},
		[T_RPAREN] = {ACT_REDUCE, 16},
		[T_EOF] = {ACT_REDUCE, 16}
	},
	{
		[T_AND] = {ACT_REDUCE, 6},
		[T_OR] = {ACT_REDUCE, 6},
		[T_PIPE] = {ACT_REDUCE, 6},
		[T_REDIR_IN] = {ACT_REDUCE, 6},
		[T_REDIR_OUT] = {ACT_REDUCE, 6},
		[T_APPEND] = {ACT_REDUCE, 6},
		[T_WORD] = {ACT_REDUCE, 6},
		[T_IDENT] = {ACT_REDUCE, 6},
		[T_DQUOTE] = {ACT_REDUCE, 6},
		[T_SQUOTE] = {ACT_REDUCE, 6},
		[T_RPAREN] = {ACT_REDUCE, 6},
		[T_EOF] = {ACT_REDUCE, 6}
	},
	{
		[T_AND] = {ACT_REDUCE, 7},
		[T_OR] = {ACT_REDUCE, 7},
		[T_PIPE] = {ACT_REDUCE, 7},
		[T_REDIR_IN] = {ACT_REDUCE, 7},
		[T_REDIR_OUT] = {ACT_REDUCE, 7},
		[T_APPEND] = {ACT_REDUCE, 7},
		[T_WORD] = {ACT_REDUCE, 7},
		[T_IDENT] = {ACT_REDUCE, 7},
		[T_DQUOTE] = {ACT_REDUCE, 7},
		[T_SQUOTE] = {ACT_REDUCE, 7},
		[T_RPAREN] = {ACT_REDUCE, 7},
		[T_EOF] = {ACT_REDUCE, 7}
	},
	{
		[T_AND] = {ACT_REDUCE, 8},
		[T_OR] = {ACT_REDUCE, 8},
		[T_PIPE] = {ACT_REDUCE, 8},
		[T_REDIR_IN] = {ACT_REDUCE, 8},
		[T_REDIR_OUT] = {ACT_REDUCE, 8},
		[T_APPEND] = {ACT_REDUCE, 8},
		[T_WORD] = {ACT_REDUCE, 8},
		[T_IDENT] = {ACT_REDUCE, 8},
		[T_DQUOTE] = {ACT_REDUCE, 8},
		[T_SQUOTE] = {ACT_REDUCE, 8},
		[T_RPAREN] = {ACT_REDUCE, 8},
		[T_EOF] = {ACT_REDUCE, 8}
	},
	{
		[T_AND] = {ACT_SHIFT, 15},
		[T_OR] = {ACT_SHIFT, 16},
		[T_RPAREN] = {ACT_SHIFT, 27},
	},
	{
		[T_AND] = {ACT_REDUCE, 1},
		[T_OR] = {ACT_REDUCE, 1},
		[T_PIPE] = {ACT_SHIFT, 17},
		[T_RPAREN] = {ACT_REDUCE, 1},
		[T_EOF] = {ACT_REDUCE, 1}
	},
	{
		[T_AND] = {ACT_REDUCE, 2},
		[T_OR] = {ACT_REDUCE, 2},
		[T_PIPE] = {ACT_SHIFT, 17},
		[T_RPAREN] = {ACT_REDUCE, 2},
		[T_EOF] = {ACT_REDUCE, 2}
	},
	{
		[T_AND] = {ACT_REDUCE, 4},
		[T_OR] = {ACT_REDUCE, 4},
		[T_PIPE] = {ACT_REDUCE, 4},
		[T_REDIR_IN] = {ACT_SHIFT, 11},
		[T_REDIR_OUT] = {ACT_SHIFT, 12},
		[T_APPEND] = {ACT_SHIFT, 13},
		[T_WORD] = {ACT_SHIFT, 7},
		[T_IDENT] = {ACT_SHIFT, 8},
		[T_DQUOTE] = {ACT_SHIFT, 9},
		[T_SQUOTE] = {ACT_SHIFT, 10},
		[T_RPAREN] = {ACT_REDUCE, 4},
		[T_EOF] = {ACT_REDUCE, 4}
	},
	{
		[T_AND] = {ACT_REDUCE, 18},
		[T_OR] = {ACT_REDUCE, 18},
		[T_PIPE] = {ACT_REDUCE, 18},
		[T_REDIR_IN] = {ACT_REDUCE, 18},
		[T_REDIR_OUT] = {ACT_REDUCE, 18},
		[T_APPEND] = {ACT_REDUCE, 18},
		[T_WORD] = {ACT_REDUCE, 18},
		[T_IDENT] = {ACT_REDUCE, 18},
		[T_DQUOTE] = {ACT_REDUCE, 18},
		[T_SQUOTE] = {ACT_REDUCE, 18},
		[T_RPAREN] = {ACT_REDUCE, 18},
		[T_EOF] = {ACT_REDUCE, 18}
	},
};

#endif
