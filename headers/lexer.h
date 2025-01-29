/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:54:58 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/29 04:09:13 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <libft.h>

# define LEX_NB 15

typedef enum e_token_type
{
	T_WORD,
	T_IDENT,
	T_NUMBER,
	T_SPACE,
	T_PIPE,
	T_OR,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HERE_DOC,
	T_APPEND,
	T_WILDCARD,
	T_AND,
	T_LBRACKET,
	T_RBRACKET,
	T_SQUOTE,
	T_DQUOTE,
	T_ERROR
}	t_token_type;

typedef struct s_token_pattern
{
	t_token_type	type;
	int				(*match)(const char *);
}	t_token_pattern;

typedef struct s_token
{
	t_token_type	type;
	size_t			start;
	size_t			len;
}	t_token;

int		match_squote(const char *s);
int		match_dquote(const char *s);
int		match_ident(const char *s);
int		match_word(const char *s);
int		match_number(const char *s);
int		match_here_doc(const char *s);
int		match_append(const char *s);
int		match_and(const char *s);
int		match_or(const char *s);
int		match_space(const char *s);
int		match_pipe(const char *s);
int		match_redir_in(const char *s);
int		match_redir_out(const char *s);
int		match_lbracket(const char *s);
int		match_rbracket(const char *s);

bool	is_chr_word(char c);
bool	tokenize(const char *str, t_collection *tokens);

#endif
