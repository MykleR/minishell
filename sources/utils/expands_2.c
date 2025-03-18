/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mykle@42angouleme.fr>               +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:23:51 by mykle             #+#    #+#             */
/*   Updated: 2025/03/18 05:10:51 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**expand_complex(const char **args, t_hmap *env, int *argc)
{
	char			**expanded;
	t_collection	res;

	if (__builtin_expect(!args || !*args || !env, 0))
		return ((char **)args);
	collection_init(&res, sizeof(char **), 32, (t_clear_info){alloc_f, T_HEAP});
	while (*args)
	{
		expanded = expand_simple(*args, env, NULL);
		while (expanded && *expanded)
			collection_append(&res, expanded++);
		args++;
	}
	if (argc)
		*argc = res.len;
	collection_append(&res, &(char *){NULL});
	return ((char **)res.data);
}

void	array_free(char **array)
{
	char	**tmp;

	tmp = array;
	while (*tmp)
		alloc_f(*tmp++);
	alloc_f(array);
}
