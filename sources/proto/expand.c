/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:08:06 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/14 15:52:53 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft_string.h"
#include "minishell.h"
#include "proto.h"
#include <stdio.h>

char	*detect_envar(char *str, int *len)
{
	int		i;
	int		j;
	int		k;
	char	tmp[4096];

	i = 0;
	while (str[i])
	{
		j = i;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		k = 0;
		while (j < i)
			tmp[k++] = str[j++];
		tmp[k] = '\0';
		*len = (int)ft_strlen(tmp);
		return (ft_strdup(tmp));
		i++;
	}
	return (str);
}

char	*search_env_var(t_hmap *h, char *str, int *len)
{
	char	**tmp;

	tmp = (char **)hmap_get(h, detect_envar(str, len));
	if (tmp == NULL)
		return (NULL);
	else
		return (*tmp);
}

char	*expand_basic(t_hmap *h, char *str, char *buff)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+')
		{
			tmp = search_env_var(h, str + i + 1, &len);
			if (tmp)
			{
				j = 0;
				while (j < (int)ft_strlen(tmp))
					buff[k++] = tmp[j++];
				i += len + 1;
				continue ;
			}
		}
		buff[k++] = str[i++];
	}
	return (buff);
}

char	*expand_squote(char *str, char *buff)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		buff[i] = str[i];
		i++;
	}
	return (buff);
}

int	expand(t_hmap *h, char *str)
{
	char	buff[4096];
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && str[i] == '\'')
			quote = 1;
		if (!quote && str[i] == '"')
			quote = 2;
		i++;
	}
	if (!quote || quote == 2)
		expand_basic(h, str, buff);
	if (quote == 1)
		expand_squote(str, buff);
	printf("%s\n", buff);
	return (0);
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	if (ac > 1)
	{
		printf("Input: %s\n", av[1]);
		init_env(ep, &c);
		expand(&c, av[1]);
	}
}
