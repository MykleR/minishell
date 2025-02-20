/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:08:32 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/20 01:23:41 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_action get_action(int state, int terminal)
{
    if (state < 0 || state >= S_COUNT || terminal < 0 || terminal > T_COUNT)
        return (t_action){ACT_ERROR, -1};
    return action_table[state][terminal];
}

t_ast_node	*lalr_parse(t_collection *tokens)
{
	(void)tokens;
	(void) get_action;
	return (NULL);
}
