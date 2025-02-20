/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:39:48 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/19 17:45:31 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	match_here_doc(const char *s)
{
	return ((*s == '<' && s[1] == '<') + (*s == '<' && s[1] == '<'));
}

int	match_append(const char *s)
{
	return ((*s == '>' && s[1] == '>') + (*s == '>' && s[1] == '>'));
}

int	match_and(const char *s)
{
	return ((*s == '&' && s[1] == '&') + (*s == '&' && s[1] == '&'));
}

int	match_or(const char *s)
{
	return ((*s == '|' && s[1] == '|') + (*s == '|' && s[1] == '|'));
}
