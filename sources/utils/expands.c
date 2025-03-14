/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:28:37 by mykle             #+#    #+#             */
/*   Updated: 2025/03/14 18:50:23 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_value(t_hmap *env, const char *str, int var_len)
{
	char		*var_name;
	const char	*value;
	
	value = "";
	var_name = ft_substr(str, 0, var_len);
	if (hmap_get(env, var_name))
		value = *(char **)hmap_get(env, var_name);
	alloc_f(var_name);
	return (ft_strdup(value));
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	alloc_f(s1);
	if (s2 != NULL)
		alloc_f(s2);
	return (result);
}

char	*replace_var(const char *str, t_hmap *env)
{
	char	*result;
	size_t	i;
	size_t	last;
	int		var_len;
	char	*var_value;

	result = NULL;
	i = -1;
	last = 0;
	while (str[++i])
	{
		if (str[i] != '$')
			continue ;
		result = join_and_free(result, ft_substr(str, last, i - last));
		var_len = match_ident(str + i + 1);
		if (var_len > 0)
		{
			var_value = get_var_value(env, &str[i + 1], var_len);
			result = join_and_free(result, var_value);
			i += var_len;
		}
		else
			result = join_and_free(result, ft_strdup("$"));
		last = i + 1;
	}
	return (join_and_free(result, ft_substr(str, last, i - last)));
}

char	**expand(const char *str, t_hmap *env)
{
	(void)env;
	(void)str;
	return (NULL);
}
