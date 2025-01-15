/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:54:58 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/15 14:58:27 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// WORD: (Cmd or Args, ect...)
// PIPE: |
// REDIRECT_IN: <
// REDIRECT_OUT: >
// HEREDOC: <<
// APPEND: >>
// BACKGROUND: &
// SEMICOLON: ;
// AND: &&
// OR: ||
// DOUBLE_QUOTE: "
// SINGLE_QUOTE: '
// WHITE_SPACE: \t \n \v \f \r
// EOF_: \0
// ERROR: Error Token

typedef enum e_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND,
	BACKGROUND,
	SEMICOLON,
	AND,
	OR,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	WHITE_SPACE,
	EOF_,
	ERROR
}				t_type;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
}				t_quote;

typedef struct s_token
{
	t_type		type;
	char		*value;
	int			len;
}				t_token;

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
	t_quote		qstate;
}				t_lexer;

#endif
