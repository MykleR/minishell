/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:19:03 by mykle             #+#    #+#             */
/*   Updated: 2025/03/11 23:12:27 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
