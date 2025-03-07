/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:50:02 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 17:25:39 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * TODO: IMPLEMENT EXPANSION AND EXPAND ARGUMENTS
*/

static int	handle_builtins(t_cmd_expr *cmd, t_hmap *env)
{
	int								i;
	const char						**argv;
	static const t_match_builtin	blts[NB_BUILTINS] = {
	{"cd", builtin_cd}, {"pwd", builtin_pwd}, {"exit", builtin_exit},
	{"unset", builtin_unset}};

	i = -1;
	argv = (const char **)cmd->argv + 1;
	while (++i < NB_BUILTINS)
		if (!ft_strcmp(blts[i].name, *cmd->argv))
			return (blts[i].func(argv, cmd->argc - 1, env));
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
		exit(execvp(cmd->argv[0], cmd->argv) + 128);
	status = query_child(pid);
	if (status)
		return (error(E_NOTCMD, cmd->argv[0]) * status);
	return (EXIT_SUCCESS);
}
