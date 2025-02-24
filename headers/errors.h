/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:55:39 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/24 21:04:26 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <unistd.h>

# define NB_ERRORS 10

# define E_MSG_OK "OK.\n\0"
# define E_MSG_LEX "Syntax error near unexpected token\n\0"
# define E_MSG_AST "Syntax error near unexpected token\n\0"
# define E_MSG_CLOSE "Syscall close unexpectedly failed\n\0"
# define E_MSG_WRITE "Syscall write unexpectedly failed\n\0"
# define E_MSG_FORK "Syscall fork unexpectedly failed\n\0"
# define E_MSG_OPEN "Syscall open unexpectedly failed\n\0"
# define E_MSG_PIPE "Syscall pipe unexpectedly failed\n\0"
# define E_MSG_DUP2 "Syscall dup2 unexpectedly failed\n\0"
# define E_MSG_SIG "Syscall sigaction unexpectedly failed\n\0"

typedef enum e_errors_type
{
	E_OK = 0,
	E_PARSE_LEX	= E_OK + sizeof(E_MSG_OK) - 1,
	E_PARSE_AST	= E_PARSE_LEX + sizeof(E_MSG_LEX) - 1,
	E_SYS_CLOSE	= E_PARSE_AST + sizeof(E_PARSE_AST) - 1,
	E_SYS_WRITE	= E_SYS_CLOSE + sizeof(E_SYS_CLOSE) - 1,
	E_SYS_FORK	= E_SYS_WRITE + sizeof(E_SYS_WRITE) - 1,
	E_SYS_OPEN	= E_SYS_FORK + sizeof(E_SYS_FORK) - 1,
	E_SYS_PIPE	= E_SYS_OPEN + sizeof(E_SYS_OPEN) - 1,
	E_SYS_DUP2	= E_SYS_PIPE + sizeof(E_SYS_PIPE) - 1,
	E_SYS_SIG	= E_SYS_DUP2 + sizeof(E_SYS_DUP2) - 1,
}	t_error_type;

void	error_print(t_error_type e);

#endif
