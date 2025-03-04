/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:50:02 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/04 01:05:56 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	execute_cmd(t_cmd_expr *cmd)
{
	pid_t	pid;

	if (__builtin_expect(!cmd || cmd->argc < 0 || !cmd->argv, 0))
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		execvp(cmd->argv[0], cmd->argv);
		ft_printf("Command '%s' not found.\n", cmd->argv[0]);
		exit(127);
	}
	return (query_child(pid));
}
