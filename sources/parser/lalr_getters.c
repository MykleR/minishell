/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:37:37 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/24 19:30:42 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_n_terminal	lalr_get_prod(int rule)
{
	if (rule < 0 || rule >= NB_PROD)
		return (0);
	return (PRODUCTIONS[rule]);
}

int	lalr_get_rhs(int rule)
{
	if (rule < 0 || rule >= NB_PROD)
		return (0);
	return (RHS_LENS[rule]);
}

int	lalr_get_goto(int rule, int state)
{
	if (state < 0 || state >= NB_STATE
		|| rule < 0 || rule >= NB_PROD)
		return (0);
	return (GOTO_VALUES[state * NB_NTERM + lalr_get_prod(rule)]);
}

t_action	lalr_get_action(int state, t_terminal term)
{
	uint32_t	index;

	index = state * NB_TERM + term;
	if (state < 0 || state >= NB_STATE || term < 0 || term >= NB_TERM)
		return ((t_action){ACT_ERROR, -1});
	return ((t_action){ACTION_TYPES[index], ACTION_VALUES[index]});
}
