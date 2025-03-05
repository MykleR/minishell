/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:37:17 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 17:09:36 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	token_clear(t_token *token)
{
	if (!token)
		return ;
	alloc_f((void *)token->val);
}

void	__token_iprint(t_token *token, void *arg)
{
	(void) arg;
	if (!token)
		return ;
	ft_printf("%d:[%s]\n", token->type, token->val);
}

bool	is_chr_word(char c, const char *banned)
{
	if (!ft_isprint(c))
		return (false);
	while (banned && *banned && *banned != c)
		banned++;
	return (!banned || !(*banned));
}

const t_pattern	*get_patterns(bool dquote)
{
	static const t_pattern	m_patterns[LEX_NB] = {
	{T_WORD, match_word}, {T_IDENT, match_ident},
	{T_SPACE, match_space}, {T_PIPE, match_pipe},
	{T_REDIR_OUT, match_redir_out}, {T_AND, match_and},
	{T_REDIR_IN, match_redir_in}, {T_OR, match_or},
	{T_HERE_DOC, match_here_doc}, {T_APPEND, match_append},
	{T_SQUOTE, match_squote}, {T_DQUOTE, match_dquote},
	{T_LPAREN, match_lparen}, {T_RPAREN, match_rparen}};
	static const t_pattern	d_patterns[LEX_STR_NB] = {
	{T_WORD, match_word},
	{T_IDENT, match_ident}};

	if (dquote)
		return (d_patterns);
	return (m_patterns);
}
