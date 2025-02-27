/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_prods.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:41:03 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/27 01:32:39 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_ast			*production(int	rule, t_ast **rhs_nodes)
{
	(void)rhs_nodes;
	switch(rule)
	{
		case (0):break;
		default: break;
	}
	return (NULL);
}
