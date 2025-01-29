/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:47:56 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 03:52:32 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	match_pipe(const char *s)
{
	return (*s == '|');
}

int	match_redir_in(const char *s)
{
	return (*s == '<');
}

int	match_redir_out(const char *s)
{
	return (*s == '>');
}

int	match_lbracket(const char *s)
{
	return (*s == '(');
}

int	match_rbracket(const char *s)
{
	return (*s == ')');
}
