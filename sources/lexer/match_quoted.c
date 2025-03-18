/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_quoted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:59:39 by mykle             #+#    #+#             */
/*   Updated: 2025/03/18 02:21:04 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	match_squote(const char *s)
{
	return (match_quote(s, '\''));
}

int	match_dquote(const char *s)
{
	return (match_quote(s, '"'));
}

int	match_nquote(const char *s)
{
	return (match_word(s, LEX_QUOTE_NOTWORD));
}
