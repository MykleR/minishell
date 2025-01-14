/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:23:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/14 19:34:38 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	__handler(int num)
{
	(void) num;
	exit(EXIT_SUCCESS);
}

__attribute__((destructor))
static void	__cleanup(void)
{
	rl_clear_history();
}

int	main(void)
{
	char	*buf;

	if (!sigs_add_handler((t_sig_handler)__handler,
			SIG_SIMPLE, 2, SIGINT, SIGTERM))
		exit(EXIT_FAILURE);
	buf = readline(">> ");
	while (buf)
	{
		if (strlen(buf) > 0)
			add_history(buf);
		printf("[%s]\n", buf);
		free(buf);
		buf = readline(">> ");
	}
	return (EXIT_SUCCESS);
}
