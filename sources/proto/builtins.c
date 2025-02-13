/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/13 13:14:04 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection.h"
#include "libft.h"
#include "libft_string.h"
#include "proto.h"
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Need to rework pwd (add protec)
void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
}

void	export_env(t_hm *h, char *key, char *value)
{
	if (!value)
		hm_set(h, key, &((char *){ft_strdup("")}));
	else
		hm_set(h, key, &((char *){ft_strdup(value)}));
}
