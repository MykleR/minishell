/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:19:03 by mykle             #+#    #+#             */
/*   Updated: 2025/03/12 21:17:58 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__env_export(t_hmap_bucket *bucket, t_collection *res)
{
	char		*value;
	char		*tmp;
	uint32_t	i;

	i = -1;
	while (bucket && ++i < bucket->keys.len)
	{
		value = ((char **)bucket->values.data)[i];
		tmp = ft_strjoin(((char **)bucket->keys.data)[i], "=");
		collection_append(res, &(char *){ft_strjoin(tmp, value)});
		alloc_f(tmp);
	}
}

void	__env_print_ex(t_hmap_bucket *bucket, void *arg)
{
	const char	*key;
	const char	*value;
	uint32_t	i;

	(void)arg;
	i = -1;
	while (bucket && ++i < bucket->keys.len)
	{
		key = ((char **)bucket->keys.data)[i];
		value = ((char **)bucket->values.data)[i];
		if (!value)
			ft_printf("declare -x %s\n", key);
		else
			ft_printf("declare -x %s=\"%s\"\n", key, value);
	}
}

void	__env_print_ev(t_hmap_bucket *bucket, void *arg)
{
	const char	*key;
	const char	*value;
	uint32_t	i;

	(void)arg;
	i = -1;
	while (bucket && ++i < bucket->keys.len)
	{
		key = ((char **)bucket->keys.data)[i];
		value = ((char **)bucket->values.data)[i];
		if (!value)
			continue ;
		ft_printf("%s=%s\n", key, value);
	}
}

int	env_init(t_hmap *env, const char **envp)
{
	char	*key;
	char	*value;

	while (*envp)
	{
		key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		value = ft_strdup(ft_strchr(*envp, '=') + 1);
		hmap_set(env, key, &value);
		alloc_f(key);
		envp++;
	}
	return (E_OK);
}

char	**env_to_array(t_hmap *env)
{
	t_collection	res;

	collection_init(&res, sizeof(char **), hmap_len(env) + 1,
		(t_clear_info){alloc_f, T_HEAP});
	collection_iter(env, (void *)&res, (t_iter_callb)__env_export);
	collection_append(&res, &(char *){NULL});
	return ((char **)res.data);
}
