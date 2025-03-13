/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:08:06 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/13 13:37:33 by thomarna         ###   ########.fr       */
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

char	*expand_basic(t_hmap *h, char *str, char *buff, int *j)
{
	char	*tmp;

	tmp = *(char **)hmap_get(h, detect_envar(str));
	if (tmp)
	{
		while (*tmp)
			buff[(*j)++] = *tmp++;
		while (*str && *str != ' ')
			str++;
	}

	return (str);
}

char	*expand_squote(char *str, char *buff, int *j)
{
	printf("Single quote\n");
	while (*str && *str != '\'')
		buff[(*j)++] = *str++;
	return (str);
}

char	*expand_dquote(t_hmap *h, char *str, char *buff, int *j)
{
	char	*tmp;

	printf("dquote\n");
	while (*str && *str != '"')
	{
		if (*str == '+')
		{
			tmp = *(char **)hmap_get(h, detect_envar(str));
			if (tmp)
			{
				while (*tmp)
					buff[(*j)++] = *tmp++;
				while (*str && *str != ' ')
					str++;
				continue ;
			}
		}
		else
			buff[(*j)++] = *str;
		str++;
	}
	return (str);
}

int	expand(t_hmap *h, char *str)
{
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
		printf("%d\n", squote);
		if (str[i] == '\'')
		{
			squote = !squote;
			if (squote)
				str = expand_squote(str + 1, buff, &j);
		}
		else if (str[i] == '"')
		{
			dquote = !dquote;
			if (dquote)
				str = expand_dquote(h, str + 1, buff, &j);
		}
		else if (str[i] == '+' && !squote && !dquote)
		{
			printf("before basic: %s\n", str);
			str = expand_basic(h, str, buff, &j);
			printf("After basic: %s\n", str);

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
	}
}
