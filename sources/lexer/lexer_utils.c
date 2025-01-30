/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:37:17 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/30 15:01:36 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	{T_NUMBER, match_number}, {T_HERE_DOC, match_here_doc},
	{T_APPEND, match_append}, {T_AND, match_and},
	{T_SQUOTE, match_squote}, {T_DQUOTE, match_dquote},
	{T_SPACE, match_space}, {T_PIPE, match_pipe},
	{T_REDIR_IN, match_redir_in}, {T_WORD, match_word},
	{T_LBRACKET, match_lbracket}, {T_RBRACKET, match_rbracket},
	{T_REDIR_OUT, match_redir_out}, {T_IDENT, match_ident},
	{T_OR, match_or}};
	static const t_pattern	d_patterns[LEX_STR_NB] = {
	{T_NUMBER, match_number}, {T_WORD, match_word},
	{T_IDENT, match_ident}};

	if (dquote)
		return (d_patterns);
	return (m_patterns);
}
