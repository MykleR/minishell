/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:23:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 05:19:35 by mrouves          ###   ########.fr       */
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

static void __tokens_iter(void *ptr, void *arg)
{
	t_token	*token;
	char	*str;

	str = arg;
	token = ptr;
	if (!token)
		return ;
	ft_printf("%d:[", token->type);
	write(1, str + token->start, token->len);
	ft_printf("], ");
}

__attribute__((destructor))
static void	__cleanup(void)
{
	rl_clear_history();
}

static void	prompt_line(t_shell *shell, const char *prompt)
{
	char	*buf;

	buf = readline(prompt);
	while (buf)
	{
		if (ft_strlen(buf) > 0)
			add_history(buf);
		shell->cmd = buf;
		tokenize(buf, &shell->tokens);
		collection_iter(&shell->tokens, (void *)buf, __tokens_iter);
		collection_clear(&shell->tokens);
		ft_printf("\n");
		free(buf);
		buf = readline(prompt);
	}
}

int	main(void)
{
	static t_shell	shell = {0};

	if (!sig_handle(SIGINT, (t_sig_callb)__sigint_callb, SIG_SIMPLE)
		|| !sig_handle(SIGQUIT, (t_sig_callb){0}, SIG_IGNORE)
		|| !shell_init(&shell))
		exit(EXIT_FAILURE);
	prompt_line(&shell, ">> ");
	shell_destroy(&shell);
	return (EXIT_SUCCESS);
}
