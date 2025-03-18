/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:26:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/18 02:01:37 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	match_quote(const char *s, char c)
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

int	match_word(const char *s, const char *not_word)
{
	int	pos;

	pos = 0;
	while (ft_isprint(s[pos]) && !ft_strchr(not_word, s[pos]))
		pos++;
	return (pos);
}

int	match_arg(const char *s)
{
	int	total_len;
	int	len;

	len = 1;
	total_len = 0;
	while (len && s[total_len])
	{
		len = match_word(s + total_len, LEX_NOTWORD)
			+ match_quote(s + total_len, '"')
			+ match_quote(s + total_len, '\'');
		total_len += len;
	}
	return (total_len);
}

int	match_space(const char *s)
{
	int	pos;

	pos = 0;
	while (ft_isspace(s[pos]))
		pos++;
	return (pos);
}

int	match_ident(const char *s)
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
