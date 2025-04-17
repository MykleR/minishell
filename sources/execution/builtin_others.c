/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 04:30:37 by mrouves           #+#    #+#             */
/*   Updated: 2025/04/17 16:10:14 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_env(const char **args, int argc, t_hmap *env)
{
	(void)args;
	(void)argc;
	collection_iter(env, NULL, (t_iter_callb)__env_print_ev);
	return (EXIT_SUCCESS);
}

int	builtin_unset(const char **args, int argc, t_hmap *env)
{
	while (argc--)
		if (ft_strcmp(args[argc], "?"))
			hmap_unset(env, args[argc]);
	return (EXIT_SUCCESS);
}

int	builtin_pwd(const char **args, int argc, t_hmap *env)
{
	char	buffer[PATH_MAX];

	(void)args;
	(void)argc;
	(void)env;
	if (getcwd(buffer, PATH_MAX))
	{
		ft_printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	return (error(E_ERROR, "pwd"));
}

int	builtin_exit(const char **args, int argc, t_hmap *env)
{
	int64_t	exit_code;

	(void)env;
	exit_code = 0;
	if (hmap_get(env, "?"))
		exit_code = ft_atoi(*(char **)hmap_get(env, "?"));
	if (isatty(STDIN_FILENO))
		ft_dprintf(STDERR_FILENO, "exit\n");
	if (argc && args[0] && !ft_safe_atoi64(args[0], &exit_code))
	{
		error(E_NUMERIC, "exit", args[0]);
		exit(2);
	}
	if (argc <= 1)
		exit(exit_code);
	return (error(E_TOOMANY, "exit"));
}

int	builtin_rickroll(const char **args, int argc, t_hmap *env)
{
	static char				*cmd_left[4] = {
		"/bin/curl", "-L", "http://bit.ly/10hA8iC", NULL};
	static char				*cmd_right[2] = {"/bin/bash", NULL};
	static t_ast			left = {.type = AST_CMD, .expr = {.cmd = {.args = {
		.len = 4, .cap = 4, .data = cmd_left}}}};
	static t_ast			right = {.type = AST_CMD, .expr = {.cmd = {.args = {
		.len = 2, .cap = 2, .data = cmd_right}}}};
	static t_binary_expr	pipe = {.left = &left, .right = &right};

	(void)args;
	(void)argc;
	return (execute_pipe(&pipe, env));
}
