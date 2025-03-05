/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:21:44 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 17:09:30 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static int	find_token(const t_pattern *patterns, int nb_patterns,
				const char *input, t_terminal *type)
{
	int	max_len;
	int	len;
	int	i;

	i = -1;
	max_len = 0;
	*type = T_WORD;
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

int	tokenize(const char *cmd, t_collection *tokens)
{
	const t_pattern	*patterns;
	t_terminal		type;
	int				len;

	if (__builtin_expect(!cmd || !tokens, 0))
		return (E_PARSE_LEX);
	patterns = get_patterns(false);
	while (*cmd)
	{
		len = find_token(patterns, LEX_NB, cmd, &type);
		if (!len)
			return (E_PARSE_LEX);
		if (type != T_SPACE)
			collection_append(tokens, &((t_token){
					type, ft_substr(cmd, 0, len)}));
		cmd += len;
	}
	collection_append(tokens, &((t_token){T_EOF, 0}));
	return (E_OK);
}
