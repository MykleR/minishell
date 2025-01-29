/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:21:44 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 04:31:11 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

bool	is_chr_word(char c)
{
	return (ft_isprint(c) && !ft_isspace(c) && c != '\''
		&& c != '"' && c != '&' && c != '|'
		&& c != '\\' && c != ';' && c != '<'
		&& c != '>' && c != '$' && c != '*');
}

static int	find_token(t_token_pattern *patterns, const char *input,
				t_token_type *type)
{
	int	max_len;
	int	len;
	int	i;

	i = -1;
	max_len = 0;
	*type = T_ERROR;
	while (++i < LEX_NB)
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

bool	tokenize(const char *input, t_collection *tokens)
{
	int						len;
	const char				*start;
	t_token_type			type;
	static t_token_pattern	patterns[LEX_NB] = {{T_NUMBER, match_number},
	{T_HERE_DOC, match_here_doc}, {T_APPEND, match_append}, {T_AND, match_and},
	{T_SQUOTE, match_squote}, {T_DQUOTE, match_dquote}, {T_OR, match_or},
	{T_PIPE, match_pipe}, {T_REDIR_IN, match_redir_in}, {T_WORD, match_word},
	{T_REDIR_OUT, match_redir_out}, {T_RBRACKET, match_rbracket},
	{T_LBRACKET, match_lbracket}, {T_IDENT, match_ident}, {T_SPACE, match_space}
	};

	start = input;
	while (*input)
	{
		len = find_token(patterns, input, &type);
		if (!len)
			return (false);
		collection_append(tokens, &((t_token){type, input - start, len}));
		input += len;
	}
	return (true);
}
