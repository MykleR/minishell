/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:55:39 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 20:34:43 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <unistd.h>

# define NB_ERRORS 10

# define ERROR_MSGS "\
	OK.\n\x00\
	Syntax error near unexpected token\n\x00\
	Syntax error near unexpected token\n\x00\
	Syscall close unexpectedly failed\n\x00\
	Syscall write unexpectedly failed\n\x00\
	Syscall fork unexpectedly failed\n\x00\
	Syscall open unexpectedly failed\n\x00\
	Syscall pipe unexpectedly failed\n\x00\
	Syscall dup2 unexpectedly failed\n\x00\
	Syscall sigaction unexpectedly failed\n"

typedef enum e_errors_type
{
	E_OK = 0,
	E_PARSE_LEX = 4,
	E_PARSE_AST = 40,
	E_SYS_CLOSE = 76,
	E_SYS_WRITE = 111,
	E_SYS_FORK = 146,
	E_SYS_OPEN = 180,
	E_SYS_PIPE = 214,
	E_SYS_DUP2 = 248,
	E_SYS_SIG = 282,
}	t_error_type;

void	error_print(t_error_type e);

#endif
