/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:19:03 by mykle             #+#    #+#             */
/*   Updated: 2025/03/06 00:20:19 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_init(t_hm *env, const char **envp)
{
	char	*key;
	char	*value;

	while (*envp)
	{
		key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		value = ft_strdup(ft_strchr(*envp, '=') + 1);
		hm_set(env, key, &value);
		alloc_f(key);
		envp++;
	}
	return (E_OK);
}
