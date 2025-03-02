/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:24:02 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/02 14:42:14 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	str_print(void *ptr, void *arg)
{
	(void)arg;
	ft_printf("%s, ", *(char **)ptr);
}

int	main(void)
{
	t_collection		c;
	static t_clear_info	clr = {alloc_f, T_HEAP};

	collection_create(&c, sizeof(char **), 2, clr);
	collection_append(&c, &((char *){ft_strdup("Bonjour ")}));
	collection_append(&c, &((char *){ft_strdup("monde ! ")}));
	collection_append(&c, &((char *){ft_strdup("ca va ?")}));
	collection_remove(&c, 1);
	collection_iter(&c, NULL, str_print);
	collection_destroy(&c);
}
