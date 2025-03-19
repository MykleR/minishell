/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 02:46:54 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/19 11:31:39 by mrouves          ###   ########.fr       */
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

static int	heredoc_process(int fd, const char *eof, bool expand, t_hmap *env)
{
	const char	*prompt = HEREDOC_PROMPT;
	char		*line;
	pid_t		pid;

	if (fd < 0)
		return (EXIT_FAILURE);
	pid = safe_fork();
	if (pid)
		return (query_child(pid));
	sig_exit();
	if (!isatty(STDIN_FILENO))
		prompt = "";
	line = readline(prompt);
	while (line && ft_strcmp(line, eof))
	{
		if (expand)
			ft_putendl_fd(expand_vars(line, env), fd);
		else
			ft_putendl_fd(line, fd);
		free(line);
		line = readline(prompt);
	}
	free(line);
	safe_close(fd);
	exit(EXIT_SUCCESS);
}

static int	heredoc_handle(t_token *token, t_token *arg,
				t_hmap *env, t_collection *files)
{
	char	*path;
	int		status;
	bool	expand;
	int		fd;

	token->type = T_REDIR_IN;
	if (!arg || arg->type != T_ARG)
		return (EXIT_SUCCESS);
	path = generate_filename();
	fd = safe_open(path, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd < 0)
		return (EXIT_FAILURE);
	collection_append(files, &(char *){ft_strdup(path)});
	expand = !ft_strchr(arg->val, '\'') && !ft_strchr(arg->val, '\"');
	arg->val = ft_strremove_f(arg->val, "\"\'");
	status = heredoc_process(fd, arg->val, expand, env);
	safe_close(fd);
	alloc_f((void *)arg->val);
	arg->val = path;
	return (status);
}

int	heredoc_parse(t_collection *tokens, t_collection *files,
		t_hmap *env, int *status)
{
	t_token		*token;
	t_token		*arg;
	uint32_t	i;

	if (__builtin_expect(!tokens || !status, 0))
		return (E_ERROR);
	i = -1;
	while (++i < tokens->len - 1)
	{
		token = collection_get(tokens, i);
		arg = collection_get(tokens, i + 1);
		if (!token || token->type != T_HEREDOC)
			continue ;
		*status = heredoc_handle(token, arg, env, files);
		if (*status)
			return (E_ERROR);
	}
	return (E_OK);
}

void	__heredoc_destroy(void *ptr)
{
	if (!ptr || !*(char **)ptr)
		return ;
	unlink(*(char **)ptr);
	alloc_f(*(char **)ptr);
}
