/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:50:02 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 22:20:45 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_cmd(t_cmd_expr *cmd)
{
	pid_t	pid;

	if (!cmd || cmd->argc <= 0 || !cmd->argv)
		return (EXIT_SUCCESS);
	pid = safe_fork();
	if (!pid)
	{
		execvp(cmd->argv[0], cmd->argv);
		ft_dprintf(STDERR_FILENO, "Command '%s' not found.\n", cmd->argv[0]);
		exit(127);
	}
	return (query_child(pid));
}
