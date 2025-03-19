/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:59:39 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 05:27:19 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	check_ident(const char *s)
{
	int	pos;

	pos = 0;
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	pos++;
	while (ft_isalnum(s[pos]) || s[pos] == '_')
		pos++;
	return (pos);
}

int	check_quote(const char *s, char c)
{
	int	len;

	if ((c != '"' && c != '\'') || *s != c)
		return (0);
	len = 1;
	while (s[len] && s[len] != c)
		len++;
	if (s[len] == c)
		return (len + 1);
	return (0);
}

int	check_word(const char *s, const char *not_word)
{
	int	pos;

	pos = 0;
	while (ft_isprint(s[pos]) && !ft_strchr(not_word, s[pos]))
		pos++;
	return (pos);
}

void	token_clear(t_token *token)
{
	if (token)
		alloc_f((void *)token->val);
}
