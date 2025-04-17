/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:50:02 by mrouves           #+#    #+#             */
/*   Updated: 2025/04/17 16:10:26 by mrouves          ###   ########.fr       */
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
	{"cd", builtin_cd}, {"rickroll", builtin_rickroll}};

	i = -1;
	while (++i < NB_BUILTINS)
		if (!ft_strcmp(builts[i].name, argv[0]))
			return (builts[i].func(argv + 1, argc - 1, env));
	return (E_ERROR);
}

int	execute_cmd(t_cmd_expr *cmd, t_hmap *env)
{
	t_collection	expanded;
	const char		**argv;
	int				status;
	int				argc;
	pid_t			pid;

	if (!cmd || !cmd->args.len)
		return (EXIT_SUCCESS);
	argc = expand_complex(&cmd->args, &expanded, env);
	argv = (const char **)expanded.data;
	collection_destroy(&cmd->args);
	cmd->args = expanded;
	if (!argc || !argv)
		return (EXIT_SUCCESS);
	status = handle_builtins(argv, argc, env);
	if (status != E_ERROR)
		return (status);
	pid = fork();
	if (!pid)
	{
		sig_default();
		exec_path(argv, env);
	}
	return (query_child(pid));
}
