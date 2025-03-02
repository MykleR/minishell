/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:36 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/02 16:13:44 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "hashmap.h"
#include "minishell.h"
#include "proto.h"
#include <fcntl.h>

void	handle_redirection(t_ast *node)
{
	int	fd;

	if (node->type == AST_REDIR_IN)
	{
		fd = safe_open(node->expr.redir.file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (node->type == AST_REDIR_OUT)
	{
		fd = open(node->expr.redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			return ;
		}
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		fd = open(node->expr.redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			return ;
		}
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
}

void	execute_subshell(t_ast *node, t_hm *h)
{
	pid_t	pid;
	int		last_exit;

	last_exit = ft_atoi(hm_get(h, "?"));
	pid = fork();
	if (pid == 0)
	{
		execute_ast(node->expr.binary.left, h);
		exit(last_exit);
	}
	else if (pid > 0)
	{
		waitpid(pid, &last_exit, 0);
		last_exit = WEXITSTATUS(last_exit);
	}
	else
	{
		perror("fork");
	}
}

void	execute_pipe(t_ast *left, t_ast *right, t_hm *h)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_ast(left, h);
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_ast(right, h);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	execute_cmd(t_ast *node, t_hm *h)
{
	(void)h;
	(void)node;
}

void	execute_ast(t_ast *node, t_hm *h)
{
	int	last_exit;

	last_exit = ft_atoi(hm_get(h, "?"));
	if (!node)
		return ;
	if (node->type == AST_CMD)
		execute_cmd(node, h);
	else if (node->type == AST_PIPE)
		execute_pipe(node->expr.binary.left, node->expr.binary.left, h);
	else if (node->type == AST_AND)
	{
		execute_ast(node->expr.binary.left, h);
		if (last_exit == 0)
			execute_ast(node->expr.binary.right, h);
	}
	else if (node->type == AST_OR)
	{
		execute_ast(node->expr.binary.left, h);
		if (last_exit != 0)
			execute_ast(node->expr.binary.right, h);
	}
	else if (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_REDIR_APP)
	{
		handle_redirection(node);
		execute_ast(node->expr.binary.left, h);
	}
	else if (node->type == AST_SUBSHELL)
		execute_subshell(node, h);
	else
		printf("Error\n");
}
