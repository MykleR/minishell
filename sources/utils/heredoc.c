/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 02:46:54 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/13 06:17:48 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*generate_filename(void)
{
	static int	i = 0;
	char		*filename;
	char		*pid;
	char		*id;

	id = ft_itoa(i++);
	pid = ft_itoa(getpid());
	filename = ft_strjoins((const char *[3]){HEREDOC_PATH, pid, id}, 3, "_");
	alloc_f(pid);
	alloc_f(id);
	return (filename);
}

static int	heredoc_process(int fd, const char *eof)
{
	int		status;
	char	*line;

	sig_exit();
	status = 1;
	while (status)
	{
		line = readline(HEREDOC_PROMPT);
		status = line && ft_strcmp(line, eof);
		if (status)
			ft_putendl_fd(line, fd);
		free(line);
	}
	safe_close(fd);
	return (EXIT_SUCCESS);
}

static int	heredoc_exec(const char *eof, const char *path)
{
	int		fd;
	pid_t	pid;

	fd = safe_open(path, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (E_ERROR);
	pid = safe_fork();
	if (!pid)
		exit(heredoc_process(fd, eof));
	safe_close(fd);
	return (query_child(pid));
}

static int	heredoc_handle(t_token *token, t_token *arg)
{
	const char	*eof;
	int			status;

	token->type = T_REDIR_IN;
	if (!arg || arg->type != T_ARG)
		return (E_OK);
	eof = ft_strdup(arg->val);
	alloc_f((void *)arg->val);
	arg->val = generate_filename();
	status = heredoc_exec(eof, arg->val);
	if (status)
		unlink(arg->val);
	alloc_f((void *)eof);
	return (status);
}

int	heredoc_handler(t_collection *tokens)
{
	t_token		*token;
	t_token		*arg;
	uint32_t	i;

	i = -1;
	while (++i < tokens->len - 1)
	{
		token = collection_get(tokens, i);
		arg = collection_get(tokens, i + 1);
		if (token && token->type == T_HERE_DOC
			&& heredoc_handle(token, arg))
			return (E_ERROR);
	}
	return (E_OK);
}
