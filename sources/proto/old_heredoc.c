/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:40:09 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/02 14:45:10 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection.h"
#include "libft_string.h"
#include "minishell.h"

static void	prompt_line(const char *prompt, t_collection *c, char *delimiter)
{
	char	*buf;

	buf = readline(prompt);
	while (buf)
	{
		if (ft_strcmp(buf, delimiter) == 0)
		{
			free(buf);
			break ;
		}
		collection_append(c, &((char *){ft_strdup(buf)}));
		/* ft_printf("[%s]\n", buf); */
		free(buf);
		buf = readline(prompt);
	}
}

void	str_print(void *ptr, void *arg)
{
	(void)arg;
	ft_printf("%s, ", *(char **)ptr);
}

int	main(int ac, char **av)
{
	t_collection	c;

	if (ac < 2)
		return (0);
	collection_create(&c, sizeof(char **), 2, (t_clear_info){alloc_f, T_HEAP});
	prompt_line("> ", &c, av[1]);
	collection_iter(&c, NULL, str_print);
	collection_destroy(&c);
}
