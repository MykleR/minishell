/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mykle@42angouleme.fr>               +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:23:51 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 06:29:57 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_complex(t_collection *args, t_collection *out, t_hmap *env)
{
	t_collection	expanded;
	char			*tmp;
	uint32_t		i;
	uint32_t		j;

	if (__builtin_expect(!args || !out || args == out || !env, 0))
		return (0);
	collection_init(out, sizeof(char **), 32, (t_clear_info){alloc_f, T_HEAP});
	i = -1;
	while (args->len && ++i < args->len - 1)
	{
		expand_simple(((char **)args->data)[i], &expanded, env);
		j = -1;
		while (expanded.len && ++j < expanded.len - 1)
		{
			tmp = ft_strdup(((char **)expanded.data)[j]);
			collection_append(out, &tmp);
		}
		collection_destroy(&expanded);
	}
	collection_append(out, &(char *){NULL});
	return (out->len - 1);
}
