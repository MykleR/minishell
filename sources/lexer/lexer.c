/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:21:44 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 19:35:41 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <errors.h>

bool	is_chr_word(char c, const char *banned)
{
	if (!ft_isprint(c))
		return (false);
	while (banned && *banned && *banned != c)
		banned++;
	return (!banned || !(*banned));
}

static inline const t_token_pattern	*get_patterns(bool dquote)
{
	static const t_token_pattern	m_patterns[LEX_NB] = {
	{T_NUMBER, match_number}, {T_HERE_DOC, match_here_doc},
	{T_APPEND, match_append}, {T_AND, match_and},
	{T_SQUOTE, match_squote}, {T_DQUOTE, match_dquote},
	{T_SPACE, match_space}, {T_PIPE, match_pipe},
	{T_REDIR_IN, match_redir_in}, {T_WORD, match_word},
	{T_LBRACKET, match_lbracket}, {T_RBRACKET, match_rbracket},
	{T_REDIR_OUT, match_redir_out}, {T_IDENT, match_ident},
	{T_OR, match_or}};
	static const t_token_pattern	d_patterns[LEX_STR_NB] = {
	{T_NUMBER, match_number}, {T_WORD, match_word},
	{T_IDENT, match_ident}};

	if (dquote)
		return (d_patterns);
	return (m_patterns);
}

static int	find_token(const t_token_pattern *patterns, int nb_patterns,
				const char *input, t_token_type *type)
{
	int	max_len;
	int	len;
	int	i;

	i = -1;
	max_len = 0;
	*type = T_ERROR;
	while (++i < nb_patterns)
	{
		len = patterns[i].match(input);
		if (len > max_len)
		{
			max_len = len;
			*type = patterns[i].type;
		}
	}
	return (max_len);
}

int tokenize(const char *cmd, t_collection *tokens)
{
	const t_token_pattern	*patterns;
	const char				*start;
	t_token_type			type;
	int						len;

	start = cmd;
	patterns = get_patterns(false);
	while (*cmd)
	{
		len = find_token(patterns, LEX_NB, cmd, &type);
		if (!len || type == T_ERROR)
			return (E_PARSE_LEX);
		collection_append(tokens, &((t_token){type, cmd - start, len}));
		cmd += len;
	}
	return (E_OK);
}
