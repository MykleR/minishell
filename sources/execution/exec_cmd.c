/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:50:02 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/13 05:38:04 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_builtins(t_cmd_expr *cmd, t_hmap *env)
{
	int								i;
	const char						**argv;
	static const t_match_builtin	builts[NB_BUILTINS] = {
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"exit", builtin_exit},
	{"echo", builtin_echo},
	{"pwd", builtin_pwd},
	{"env", builtin_env},
	{"cd", builtin_cd}};

	i = -1;
	argv = (const char **)cmd->argv + 1;
	while (++i < NB_BUILTINS)
		if (!ft_strcmp(builts[i].name, cmd->argv[0]))
			return (builts[i].func(argv, cmd->argc - 1, env));
	return (E_ERROR);
}

int	execute_cmd(t_cmd_expr *cmd, t_hmap *env)
{
	struct stat	buf;
	pid_t		pid;
	int			status;

	(void)env;
	if (!cmd || cmd->argc <= 0 || !cmd->argv)
		return (EXIT_SUCCESS);
	status = handle_builtins(cmd, env);
	if (status != E_ERROR)
		return (status);
	pid = safe_fork();
	if (!pid)
	{
		sig_default();
		execvp(cmd->argv[0], cmd->argv);
		if (!stat(cmd->argv[0], &buf) && buf.st_mode & S_IFDIR)
			exit(error(E_ISDIR, cmd->argv[0]) * 126);
		exit(error(E_NOTCMD, cmd->argv[0]) * 127);
	}
	return (query_child(pid));
}
