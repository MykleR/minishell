/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:55:39 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 21:07:51 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <unistd.h>

# define NB_ERRORS 10

# define ERROR_MSGS "OK.\n\0\
Syntax error near unexpected token\n\0\
Syntax error near unexpected token\n\0\
Syscall close unexpectedly failed\n\0\
Syscall write unexpectedly failed\n\0\
Syscall fork unexpectedly failed\n\0\
Syscall open unexpectedly failed\n\0\
Syscall pipe unexpectedly failed\n\0\
Syscall dup2 unexpectedly failed\n\0\
Syscall sigaction unexpectedly failed\n"

typedef enum e_errors_type
{
	E_OK = 0,
	E_PARSE_LEX = 5,
	E_PARSE_AST = 41,
	E_SYS_CLOSE = 77,
	E_SYS_WRITE = 112,
	E_SYS_FORK = 147,
	E_SYS_OPEN = 181,
	E_SYS_PIPE = 215,
	E_SYS_DUP2 = 249,
	E_SYS_SIG = 283,
}	t_error_type;

void	error_print(t_error_type e);

#endif
