/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:54:58 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/18 02:46:29 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <utils.h>

# define LEX_NB 11
# define LEX_NB_QUOTE 3

# define LEX_NOTWORD "|&<>;\\\"' \t\r\n()"
# define LEX_QUOTE_NOTWORD "\"'"

typedef enum e_terminal
{
	T_OR		= 0,
	T_AND		= 1,
	T_PIPE		= 2,
	T_LPAREN	= 3,
	T_RPAREN	= 4,
	T_REDIR_IN	= 5,
	T_REDIR_OUT	= 6,
	T_APPEND	= 7,
	T_ARG		= 8,
	T_EOF		= 9,
	T_SPACE		= 10,
	T_HERE_DOC	= 11,
	T_DQUOTE	= 12,
	T_SQUOTE	= 13,
	T_NQUOTE	= 14,
}	t_terminal;

typedef struct s_pattern
{
	t_terminal	type;
	int			(*match)(const char *);
}	t_pattern;

typedef struct s_token
{
	t_terminal	type;
	const char	*val;
}	t_token;

int		match_arg(const char *s);
int		match_here_doc(const char *s);
int		match_append(const char *s);
int		match_and(const char *s);
int		match_or(const char *s);
int		match_space(const char *s);
int		match_pipe(const char *s);
int		match_redir_in(const char *s);
int		match_redir_out(const char *s);
int		match_lparen(const char *s);
int		match_rparen(const char *s);
int		match_ident(const char *s);
int		match_quote(const char *s, char c);
int		match_word(const char *s, const char *not_word);
int		match_nquote(const char *s);
int		match_dquote(const char *s);
int		match_squote(const char *s);

void	token_clear(t_token *token);
void	token_print(t_token *token, void *arg);

int		tokenize(const char *str, t_collection *tokens);
int		tokenize_quotes(const char *str, t_collection *tokens);

#endif
