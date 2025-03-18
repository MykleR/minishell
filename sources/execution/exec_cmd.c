/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:50:02 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/18 05:12:30 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_builtins(const char **argv, int argc, t_hmap *env)
{
	int								i;
	static const t_match_builtin	builts[NB_BUILTINS] = {
	{"export", builtin_export}, {"unset", builtin_unset},
	{"exit", builtin_exit}, {"echo", builtin_echo},
	{"pwd", builtin_pwd}, {"env", builtin_env},
	{"cd", builtin_cd}};

	i = -1;
	while (++i < NB_BUILTINS)
		if (!ft_strcmp(builts[i].name, argv[0]))
			return (builts[i].func(argv + 1, argc - 1, env));
	return (E_ERROR);
}

int	execute_cmd(t_cmd_expr *cmd, t_hmap *env)
{
	char		**expanded;
	int			argc;
	int			status;
	pid_t		pid;

	if (!cmd || !cmd->args.len)
		return (EXIT_SUCCESS);
	expanded = expand_complex((const char **)cmd->args.data, env, &argc);
	if (!expanded || argc < 1)
		return (EXIT_SUCCESS);
	status = handle_builtins((const char **)expanded, argc, env);
	if (status != E_ERROR)
		return (status);
	pid = safe_fork();
	if (!pid)
	{
		sig_default();
		exec_path(expanded, env);
	}
	return (query_child(pid));
}
