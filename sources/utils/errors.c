/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:59:51 by mykle             #+#    #+#             */
/*   Updated: 2025/03/26 12:47:50 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	error(t_error_type e, ...)
{
	va_list		av;
	char		*msg;
	const int	fd = STDERR_FILENO;
	const char	*errors = E_MSG_OK E_MSG_LEX E_MSG_AST E_MSG_OPEN \
		E_MSG_TOOMANY E_MSG_NOTCMD E_MSG_NOTSET E_MSG_NUMERIC E_MSG_IDENTIF \
		E_MSG_ISDIR E_MSG_AMBIGUOUS;

	if (e == E_OK)
		return (e);
	msg = (char *)errors + (int)e;
	va_start(av, e);
	if (e == E_ERROR)
		ft_dprintf(fd, E_MSG_ERROR, va_arg(av, char *), strerror(errno));
	else
		ft_vdprintf(fd, msg, av);
	va_end(av);
	return (EXIT_FAILURE);
}

int	try_open(const char *filename, int mode)
{
	int	fd;

	if (!filename || !*filename)
		return (E_ERROR);
	fd = cached_open(filename, mode, 0644);
	if (fd == E_ERROR)
		error(E_OPEN, "open", filename, strerror(errno));
	return (fd);
}
