/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:42:16 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/30 16:39:11 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe.h"
#include <fcntl.h>
#include <unistd.h>

#define TMP_PREFIX "ms"
#define TMP_ID 100000000

int	is_exist(const char *fname)
{
	if (access(fname, F_OK))
		return (1);
	return (0);
}

char	*random_string(int len)
{
	char			*filename;
	int				fd;
	unsigned char	*buffer;
	int				i;

	i = -1;
	buffer = malloc(sizeof(char) * len + 1);
	filename = malloc(sizeof(char) * len + 1);
	if (!filename || !buffer)
		return (NULL);
	fd = safe_open("/dev/random", O_RDONLY);
	if (safe_read(fd, buffer, len) != len)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	while (++i < len)
		filename[i] = (buffer[i] % 26) + 97;
	filename[len] = '\0';
	return (filename);
}

int	create_tmp(void)
{
	int		fd;
	char	*filename;
	char	*tmp;

	tmp = random_string(12);
	if (!tmp)
		return (-1);
	filename = ft_strjoin("/tmp/", tmp);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 644);
	return (fd);
}

static void	prompt_line(const char *prompt, int fd, char *delimiter)
{
	char	*buf;

	buf = readline(prompt);
	while (buf)
	{
		if (ft_strcmp(buf, delimiter) == 0)
		{
			free(buf);
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
		buf = readline(prompt);
	}
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac < 2)
		return (0);
	fd = create_tmp();
	if (fd == -1)
		return (1);
	prompt_line("> ", fd, av[1]);
	close(fd);
}
