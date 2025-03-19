/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:26:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/19 05:22:14 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	match_squote(const char *s)
{
	return (check_quote(s, '\''));
}

int	match_dquote(const char *s)
{
	return (check_quote(s, '"'));
}

int	match_nquote(const char *s)
{
	return (check_word(s, LEX_BAN_QUOTE));
}

int	match_space(const char *s)
{
	int	pos;

	pos = 0;
	while (ft_isspace(s[pos]))
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
		len = check_word(s + total_len, LEX_BAN)
			+ check_quote(s + total_len, '"')
			+ check_quote(s + total_len, '\'');
		total_len += len;
	}
	return (total_len);
}
