/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:26:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 22:54:42 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	match_squote(const char *s)
{
	int	len;

	len = match_word(s);
	while (match_ident(s + len))
		len += match_ident(s + len);
	if (s[len] != '\'')
		return (0);
	len++;
	while (s[len] && s[len] != '\'')
		len++;
	if (s[len] != '\'')
		return (0);
	len++;
	len += match_word(s + len);
	while (match_ident(s + len))
		len += match_ident(s + len);
	return (len);
}

int	match_dquote(const char *s)
{
	int	len;

	len = match_word(s);
	while (match_ident(s + len))
		len += match_ident(s + len);
	if (s[len] != '"')
		return (0);
	len++;
	while (s[len] && s[len] != '"')
		len++;
	if (s[len] != '"')
		return (0);
	len++;
	len += match_word(s + len);
	while (match_ident(s + len))
		len += match_ident(s + len);
	return (len);
}

int	match_ident(const char *s)
{
	int	pos;

	if (*s != '$' || !ft_isalpha(*(s + 1)))
		return (0);
	pos = 2;
	while (ft_isalnum(s[pos]) || s[pos] == '_')
		pos++;
	return (pos);
}

int	match_word(const char *s)
{
	int	pos;

	pos = 0;
	while (is_chr_word(s[pos], LEX_NOTWORD))
		pos++;
	return (pos);
}

int	match_space(const char *s)
{
	int	pos;

	pos = 0;
	while (ft_isspace(s[pos]))
		pos++;
	return (pos);
}
