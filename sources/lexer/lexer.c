/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:21:44 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/11 23:07:10 by mrouves          ###   ########.fr       */
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
	*type = T_ARG;
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

void	token_clear(t_token *token)
{
	if (token)
		alloc_f((void *)token->val);
}

int	tokenize(const char *cmd, t_collection *tokens)
{
	int						len;
	t_terminal				type;
	static const t_pattern	patterns[LEX_NB] = {
	{T_SPACE, match_space}, {T_PIPE, match_pipe}, {T_ARG, match_arg},
	{T_REDIR_OUT, match_redir_out}, {T_AND, match_and},
	{T_REDIR_IN, match_redir_in}, {T_OR, match_or},
	{T_HERE_DOC, match_here_doc}, {T_APPEND, match_append},
	{T_LPAREN, match_lparen}, {T_RPAREN, match_rparen}};

	while (cmd && *cmd)
	{
		len = find_token(patterns, LEX_NB, cmd, &type);
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
