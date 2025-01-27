/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_proto.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:45:29 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/27 21:14:50 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <libft.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

#define TOKENS_NB 11
#define TOKENS_STR {"||", "&&", "<<", ">>", "<", ">", "|", "'", "\"", "(", ")"}

typedef enum e_token_type
{
	T_OR,
	T_AND,
	T_DLESS,
	T_DGREAT,
	T_LESS,
	T_GREAT,
	T_PIPE,
	T_SQUOTE,
	T_DQUOTE,
	T_LBRACE,
	T_RBRACE,
	T_WORD,
}	t_token_type;

typedef enum e_quote_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
}	t_quote_type;

typedef struct s_token
{
	size_t			start;
	size_t			len;
	t_token_type	type;
	t_quote_type	ctx;
}	t_token;

typedef struct s_lexer
{
	size_t			i;
	t_quote_type	quote;
	t_token_type	token;
}	t_lexer;

typedef struct s_shell
{
	const char		*cmd;
	t_collection	tokens;
}	t_shell;

bool	shell_init(t_shell *shell, const char *cmd)
{
	static const t_clear_info	clear = {0};
	
	if (__builtin_expect(!shell, 0))
		return (false);
	shell->cmd = ft_strdup(cmd);
	return (shell->cmd && collection_create(
		&shell->tokens, 32, sizeof(t_token), clear));
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	collection_destroy(&shell->tokens);
	alloc_f((void *)shell->cmd);
}

t_token_type	find_token(const char *cmd, size_t *len_out)
{
	static const char	*strs[TOKENS_NB] = TOKENS_STR;
	uint8_t				i;

	i = 0;
	*len_out = 0;
	while (i < TOKENS_NB && ft_strncmp(cmd, strs[i], ft_strlen(strs[i])))
		i++;
	if (i < TOKENS_NB)
		*len_out = ft_strlen(strs[i]);
	return (i);
}

void	update_quote_context(t_lexer *lex)
{
	if (lex->quote == Q_NONE && lex->token == T_SQUOTE)
		lex->quote = Q_SINGLE;
	else if (lex->quote == Q_NONE && lex->token == T_DQUOTE)
		lex->quote = Q_DOUBLE;
	else if ((lex->token == T_SQUOTE && lex->quote == Q_SINGLE)
			|| (lex->token == T_DQUOTE && lex->quote == Q_DOUBLE))
		lex->quote = Q_NONE;
}

void	tokenize(t_collection *tokens, const char *cmd)
{
	t_lexer			lex;
	size_t			len;
	size_t			start;

	lex.i = 0;
	lex.quote = Q_NONE;
	start = 0;
	while(cmd[lex.i])
	{
		lex.token = find_token(cmd + lex.i, &len);
		if (lex.token != T_WORD)
		{
			if (start < lex.i)
				collection_append(tokens, &((t_token){start, lex.i - start, T_WORD, lex.quote}));
			collection_append(tokens, &((t_token){lex.i, len, lex.token, lex.quote}));
			start = lex.i + len;
		}
		update_quote_context(&lex);
		lex.i += len + !len;
	}
	if (cmd[start])
		collection_append(tokens, &((t_token){start, lex.i - start, T_WORD, lex.quote}));
}

void	__token_iter(void *ptr, void *arg)
{
	t_token *token;
	char	*cmd = *(char **)arg;

	token = ptr;
	if (token)
	{
		ft_printf("[%d:{", token->type);
		write(1, cmd + token->start, token->len);
		ft_printf("}]\n");
	}
}

int	main(int ac, char **av)
{
	static t_shell	shell = {0};

	if (ac != 2 || !shell_init(&shell, av[1]))
		return (1);
	tokenize(&shell.tokens, shell.cmd);
	collection_iter(&(shell.tokens), &shell.cmd, __token_iter);
	shell_destroy(&shell);
	return (0);
}
