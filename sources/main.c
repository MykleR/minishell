/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:23:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/17 02:43:51 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__sigint_callb(int num)
{
	(void) num;
	write(1, &((char){'\n'}), 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

__attribute__((destructor))
static void	__cleanup(void)
{
	rl_clear_history();
}

static void	prompt_line(const char *prompt)
{
	char	*buf;

	buf = readline(prompt);
	while (buf)
	{
		if (ft_strlen(buf) > 0)
			add_history(buf);
		ft_printf("[%s]\n", buf);
		free(buf);
		buf = readline(prompt);
	}
}

int	main(void)
{
	if (!sig_handle(SIGINT, (t_sig_callb)__sigint_callb, SIG_SIMPLE)
		|| !sig_handle(SIGQUIT, (t_sig_callb){0}, SIG_IGNORE))
		exit(EXIT_FAILURE);
	prompt_line(">> ");
	return (EXIT_SUCCESS);
}
