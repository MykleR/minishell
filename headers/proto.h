/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:00:04 by thomarna          #+#    #+#             */
/*   Updated: 2025/02/17 16:42:50 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H
# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	init_env(char **ep, t_collection *c);
char	*get_value(char *src);
char	*get_key(char *src);
void	env_builtin(t_hm *h);
char	*get_env(t_hm *h, char *key);
void	ft_pwd(void);
#endif
