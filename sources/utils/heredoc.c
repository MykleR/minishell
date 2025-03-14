/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 02:46:54 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/14 03:01:04 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*generate_filename(void)
{
	static int	i = 0;
	char		pid[12];
	char		id[12];

	ft_itoa_buf(i++, id);
	ft_itoa_buf(getpid(), pid);
	return (ft_strjoins((const char *[3]){HEREDOC_PATH, pid, id}, 3, "_"));
}

static int	heredoc_process(int fd, const char *eof)
{
	pid_t	pid;
	int		status;
	char	*line;

	if (fd < 0)
		return (E_ERROR);
	pid = safe_fork();
	if (pid)
		return (query_child(pid));
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
	exit(EXIT_SUCCESS);
}

static int	heredoc_handle(t_token *token, t_token *arg)
{
	const char	*path;
	int			fd;
	int			status;

	token->type = T_REDIR_IN;
	if (!arg || arg->type != T_ARG)
		return (E_OK);
	path = generate_filename();
	fd = safe_open(path, O_CREAT | O_WRONLY | O_TRUNC);
	status = heredoc_process(fd, arg->val);
	safe_close(fd);
	if (status)
		unlink(arg->val);
	alloc_f((void *)arg->val);
	arg->val = path;
	return (status);
}

int	heredoc_parse(t_collection *tokens)
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
