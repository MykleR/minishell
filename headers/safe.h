/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:21:50 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/30 14:40:29 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_H
# define SAFE_H

# include <stdlib.h>

int		safe_open(const char *filename, int flags);
ssize_t	safe_read(int fd, void *buffer, size_t count);
ssize_t	safe_write(int fd, const void *buffer, size_t count);
#endif
