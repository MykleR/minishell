/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:08:06 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/11 18:11:55 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "minishell.h"
#include "proto.h"

char *detect_envar(char *str)
{

	while (*str)
	{
		if (*str == '+')
		{	
			return (str + 1);
		}
		str++;
	}
	return (0);
}

int	expand(t_hmap *h, char *str)
{
	char *tmp;
	char buff[4096];
	int i;

	i = 0;
	tmp = *(char **)hmap_get(h, detect_envar(str));
	/* printf("%s\n", *(char **)tmp); */
	if (tmp)
	{
		while (str[i])
		{
			if (str[i] != '+')
				buff[i] = str[i];
			else
			{
				while (*tmp)
				{
					buff[i] = *tmp;
					tmp++;
					i++;
				}
			}
			i++;
		}
	}
	printf("%s\n", buff);
	return (0);
}

int main(int ac, char **av, char **ep)
{
	if (ac > 1) 
	{
		t_collection c;
		init_env(ep, &c);
		expand(&c, av[1]);
		/* printf("%s\n", av[1]); */
	}
}
