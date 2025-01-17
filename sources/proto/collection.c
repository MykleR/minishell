/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:24:02 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/17 16:25:09 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    str_print(void *ptr, void *arg)
{
    (void) arg;
    ft_printf("%s, ", *(char **)ptr);
}

int    main(void)
{
    t_collection    c;

    collection_create(&c, sizeof(char **), 2, alloc_f);
    collection_append(&c, &((char *){ft_strdup("Bonjour ")}));
    collection_append(&c, &((char *){ft_strdup("monde ! ")}));
    collection_append(&c, &((char *){ft_strdup("ca va ?")}));
    collection_remove(&c, 1);
    collection_iter(&c, NULL, str_print);
    collection_destroy(&c);
}
