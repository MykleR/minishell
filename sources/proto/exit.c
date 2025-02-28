/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:37:59 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/28 10:35:57 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "minishell.h"
#include "proto.h"

static int	custom_atoi(char *nptr, int *error)
{
	unsigned long long	nb;
	int					sign;

	nb = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr - 48);
		nptr++;

	}
	if (*nptr || nb > 9223372036854775807)
		*error = -1;
	return (nb * sign);
}

void	ft_exit(t_hm *h, char **args)
{
	int	res;
	int	error;

	if (args[1])
	{
		res = custom_atoi(args[1], &error);
		if (error)
			ft_printf("exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	else if (args[1] && args[2])
	{
		ft_printf("exit: too many arguments\n");
		exit(2);
	}
	else
		exit(ft_atoi(hm_get(h, "?")));
	exit(res);
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	(void)ac;
	(void)av;
	init_env(ep, &c);
	printf("$?: %s\n", *(char **)hm_get(&c, "?"));
}
