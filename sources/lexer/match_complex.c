/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:26:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 04:32:37 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	match_squote(const char *s)
{
	int	len;

	if (*s != '\'')
		return (0);
	len = 1;
	while (s[len] && s[len] != '\'')
		len++;
	if (s[len] == '\'')
		return (len + 1);
	return (0);
}

int	match_dquote(const char *s)
{
	int	len;

	if (*s != '"')
		return (0);
	len = 1;
	while (s[len] && s[len] != '"')
		len++;
	if (s[len] == '"')
		return (len + 1);
	return (0);
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
	while (is_chr_word(s[pos]))
		pos++;
	return (pos);
}

int	match_number(const char *s)
{
	int		pos;

	pos = 0;
	while (ft_isdigit(s[pos]))
		pos++;
	return (pos);
}
