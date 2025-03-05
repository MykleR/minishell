/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:54:58 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/05 17:09:13 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <utils.h>

# define LEX_NB 14
# define LEX_STR_NB 2

# define LEX_NOTWORD "|&*<>;\\\"'$ ()"
# define LEX_DQ_NOTWORD "*$\\"

typedef enum e_terminal
{
	T_AND		= 0,
	T_OR		= 1,
	T_PIPE		= 2,
	T_LPAREN	= 3,
	T_RPAREN	= 4,
	T_REDIR_IN	= 5,
	T_REDIR_OUT	= 6,
	T_APPEND	= 7,
	T_WORD		= 8,
	T_IDENT		= 9,
	T_DQUOTE	= 10,
	T_SQUOTE	= 11,
	T_EOF		= 12,
	T_SPACE		= 13,
	T_HERE_DOC	= 14,
	T_WILDCARD	= 15,
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

int				match_squote(const char *s);
int				match_dquote(const char *s);
int				match_ident(const char *s);
int				match_word(const char *s);
int				match_here_doc(const char *s);
int				match_append(const char *s);
int				match_and(const char *s);
int				match_or(const char *s);
int				match_space(const char *s);
int				match_pipe(const char *s);
int				match_redir_in(const char *s);
int				match_redir_out(const char *s);
int				match_lparen(const char *s);
int				match_rparen(const char *s);

void			token_clear(t_token *token);
void			__token_iprint(t_token *token, void *arg);
bool			is_chr_word(char c, const char *banned);
const t_pattern	*get_patterns(bool dquote);

int				tokenize(const char *str, t_collection *tokens);

#endif
