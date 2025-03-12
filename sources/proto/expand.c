/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:08:06 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/12 09:08:12 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "minishell.h"
#include "proto.h"

char	*detect_envar(char *str)
{
	while (*str)
	{
		if (*str == '+')
			return (str + 1);
		str++;
	}
	return (0);
}

int	expand(t_hmap *h, char *str)
{
	char	*tmp;
	char	buff[4096];
	int		i;
	int		j;
	int		squote;
	int		dquote;

	i = 0;
	j = 0;
	squote = 0;
	dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			squote = !squote;
		if (str[i] == '"')
			dquote = !dquote;
		if (str[i] == '+' && !squote)
		{
			/* Rajouter dans le if le check de si !(dquote && squote) ou les différents cas mais ça marche po :( */
			tmp = *(char **)hmap_get(h, detect_envar(str));
			if (tmp)
			{
				while (*tmp)
					buff[j++] = *tmp++;
				while (str[i] && str[i] != ' ')
					i++;
				continue ;
			}
		}
		else
			buff[j++] = str[i];
		i++;
	}
	buff[j] = '\0';
	printf("%s\n", buff);
	return (0);
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	if (ac > 1)
	{
		init_env(ep, &c);
		expand(&c, av[1]);
		/* printf("%s\n", av[1]); */
	}
}
