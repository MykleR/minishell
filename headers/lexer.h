/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:54:58 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/19 06:16:44 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <utils.h>

# define LEX_NB 11
# define LEX_NB_QUOTE 3

# define LEX_BAN "|&<>;\\\"' \t\r\n()"
# define LEX_BAN_QUOTE "\"'"

typedef enum e_terminal
{
	T_OR		= 0,
	T_AND		= 1,
	T_PIPE		= 2,
	T_LPAREN	= 3,
	T_RPAREN	= 4,
	T_REDIR_IN	= 5,
	T_REDIR_OUT	= 6,
	T_REDIR_APP	= 7,
	T_ARG		= 8,
	T_EOF		= 9,
	T_SPACE		= 10,
	T_HEREDOC	= 11,
	T_DQUOTE	= 12,
	T_SQUOTE	= 13,
	T_NQUOTE	= 14,
}	t_terminal;

typedef enum e_match_type
{
	MATCH_SIMPLE,
	MATCH_COMPLEX,
}	t_match_type;

typedef union u_match
{
	char		*simple;
	int			(*complex)(const char *);
}	t_match;

typedef struct s_pattern
{
	t_terminal		token;
	t_match_type	type;
	t_match			match;
}	t_pattern;

typedef struct s_token
{
	t_terminal	type;
	char		*val;
}	t_token;

int		match_arg(const char *s);
int		match_space(const char *s);
int		match_nquote(const char *s);
int		match_dquote(const char *s);
int		match_squote(const char *s);
int		check_ident(const char *s);
int		check_quote(const char *s, char c);
int		check_word(const char *s, const char *not_word);

void	token_clear(t_token *token);
void	token_print(t_token *token, void *arg);

int		tokenize_cmd(const char *str, t_collection *tokens);
int		tokenize_quotes(const char *str, t_collection *tokens);

#endif
