/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:21:44 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/19 05:33:11 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static int	token_len(const char *s, t_pattern pattern)
{
	int	pattern_len;

	if (pattern.type == MATCH_COMPLEX)
		return (pattern.match.complex(s));
	pattern_len = ft_strlen(pattern.match.simple);
	if (!ft_strncmp(s, pattern.match.simple, pattern_len))
		return (pattern_len);
	return (0);
}

static int	find_token(const t_pattern *patterns, int nb_patterns,
				const char *input, t_terminal *type)
{
	int	max_len;
	int	len;
	int	i;

	i = -1;
	max_len = 0;
	*type = T_SPACE;
	while (++i < nb_patterns)
	{
		len = token_len(input, patterns[i]);
		if (len > max_len)
		{
			max_len = len;
			*type = patterns[i].token;
		}
	}
	return (max_len);
}

static int	tokenize_pattern(const char *cmd, const t_pattern *patterns,
				int nb_patterns, t_collection *tokens)
{
	t_terminal	type;
	int			len;

	while (cmd && *cmd)
	{
		len = find_token(patterns, nb_patterns, cmd, &type);
		if (!len)
			return (error(E_PARSE_LEX, cmd));
		if (type != T_SPACE)
			collection_append(tokens, &((t_token){
					type, ft_substr(cmd, 0, len)}));
		cmd += len;
	}
	collection_append(tokens, &((t_token){T_EOF, ft_strdup("newline")}));
	return (E_OK);
}

int	tokenize_cmd(const char *cmd, t_collection *tokens)
{
	const t_pattern	patterns[LEX_NB] = {
	{T_SPACE, MATCH_COMPLEX, (t_match)match_space},
	{T_ARG, MATCH_COMPLEX, (t_match)match_arg},
	{T_REDIR_APP, MATCH_SIMPLE, {">>"}},
	{T_REDIR_OUT, MATCH_SIMPLE, {">"}},
	{T_REDIR_IN, MATCH_SIMPLE, {"<"}},
	{T_HEREDOC, MATCH_SIMPLE, {"<<"}},
	{T_LPAREN, MATCH_SIMPLE, {"("}},
	{T_RPAREN, MATCH_SIMPLE, {")"}},
	{T_PIPE, MATCH_SIMPLE, {"|"}},
	{T_AND, MATCH_SIMPLE, {"&&"}},
	{T_OR, MATCH_SIMPLE, {"||"}}};

	return (tokenize_pattern(cmd, patterns, LEX_NB, tokens));
}

int	tokenize_quotes(const char *cmd, t_collection *tokens)
{
	const t_pattern	patterns[LEX_NB_QUOTE] = {
	{T_SQUOTE, MATCH_COMPLEX, (t_match)match_squote},
	{T_DQUOTE, MATCH_COMPLEX, (t_match)match_dquote},
	{T_NQUOTE, MATCH_COMPLEX, (t_match)match_nquote}};

	return (tokenize_pattern(cmd, patterns, LEX_NB_QUOTE, tokens));
}
