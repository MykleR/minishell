/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:50:02 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 03:59:32 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_builtins(t_cmd_expr *cmd, t_hmap *env)
{
	int								i;
	static const t_match_builtin	builtins[NB_BUILTINS] = {
		{"cd", builtin_cd}, {"pwd", builtin_pwd}, {"exit", builtin_exit}};

	i = -1;
	while (++i < NB_BUILTINS)
	{
		if (!ft_strcmp(builtins[i].name, cmd->argv[0]))
			return (builtins[i].func((const char **)cmd->argv + 1,
						cmd->argc - 1, env));
	}
	return (E_ERROR);
}

int	execute_cmd(t_cmd_expr *cmd, t_hmap *env)
{
	pid_t	pid;
	int		status;

	(void)env;
	if (!cmd || cmd->argc <= 0 || !cmd->argv)
		return (EXIT_SUCCESS);
	status = handle_builtins(cmd, env);
	if (status != E_ERROR)
		return (status);
	pid = safe_fork();
	if (!pid)
	{
		execvp(cmd->argv[0], cmd->argv);
		exit(error(E_NOCMD, cmd->argv[0]) + 126);
	}
	return (query_child(pid));
}
