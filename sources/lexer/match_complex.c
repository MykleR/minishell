/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:26:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/11 22:45:55 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static bool	is_chr_word(char c, const char *banned)
{
	if (!ft_isprint(c))
		return (false);
	while (banned && *banned && *banned != c)
		banned++;
	return (!banned || !(*banned));
}

static int	match_quote(const char *s, char c)
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

static int	match_word(const char *s)
{
	int	pos;

	pos = 0;
	while (is_chr_word(s[pos], LEX_NOTWORD))
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
		len = match_word(s + total_len)
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
