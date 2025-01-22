/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_proto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:45:29 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/22 20:36:14 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <libft.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

#define NB_TOKENS 14

typedef enum e_token_type
{
	T_WORD,
	T_SEMI,
	T_PIPE,
	T_OR,
	T_AND,
	T_SQUOTE,
	T_DQUOTE,
	T_LBRACE,
	T_RBRACE,
	T_LESS,
	T_DLESS,
	T_GREAT,
	T_DGREAT,
	T_EOF,
}	t_token_type;

typedef struct s_token
{
	t_collection	str;
	t_token_type	type;
}	t_token;

typedef struct s_lexer
{
	t_collection	tokens;
	size_t			index;
	t_token_type	ctx;
}	t_lexer;

typedef struct s_shell
{
	const char		*cmd;
	t_lexer			lexer;
	t_hm			str_tokens;
}	t_shell;

bool	token_init(t_token *token, t_token_type t)
{
	static t_clear_info	clear = {0};
	
	if (__builtin_expect(!token, 0))
		return (false);
	token->type = t;
	return (collection_create(&token->str, 32, sizeof(char),clear));
}

void	token_destroy(t_token *token)
{
	if (__builtin_expect(token != NULL, 1))
		collection_destroy(&token->str);
}

bool	lexer_init(t_lexer *lexer)
{
	static const t_clear_info	clear = {
		(void (*)(void*))token_destroy, T_STACK};

	if (__builtin_expect(!lexer, 0))
		return (false);
	lexer->ctx = 0;
	lexer->index = 0;
	return (collection_create(&lexer->tokens, 32, sizeof(t_token), clear));
}

void	lexer_destroy(t_lexer *lexer)
{
	if (__builtin_expect(lexer != NULL, 1))
		collection_destroy(&lexer->tokens);
}

bool	shell_init(t_shell *shell, const char *cmd)
{
	static const t_clear_info	clear = {0};
	static const char			*strs[NB_TOKENS] = {"\\", ";", "|", "||", "&&",
		"'", "\"", "(", ")", "<", "<<", ">", ">>"};
	t_token_type				type;
	bool						success;


	if (__builtin_expect(!shell, 0))
		return (false);
	shell->cmd = ft_strdup(cmd);
	success = shell->cmd && lexer_init(&shell->lexer)
		&& hm_create(&shell->str_tokens, 32, sizeof(t_token_type), clear);
	type = -1;
	while (success && ++type < NB_TOKENS)
		hm_set(&shell->str_tokens, strs[type], &((t_token_type){type}));
	return (success);
}

void	shell_destroy(t_shell *shell)
{
	if (__builtin_expect(!shell, 0))
		return ;
	lexer_destroy(&shell->lexer);
	alloc_f((void *)shell->cmd);
}

bool	tokenize(t_shell *shell)
{
	t_token	current;

	(void) shell;
	if (!token_init(&current, T_WORD))
		return (false);
	while (current.type != T_EOF)
	{
		
	}
	return (true);
}

void	__token_iter(void *ptr, void *arg)
{
	t_token *token;

	(void) arg;
	token = ptr;
	if (token)
		ft_printf("[%d : %s], ", token->type, (char *)(token->str.data));
}

int	main(int ac, char **av)
{
	static t_shell	shell = {0};

	if (ac != 2 || !shell_init(&shell, av[1]))
		return (1);
	tokenize(&shell);
	collection_iter(&(shell.lexer.tokens), NULL, __token_iter);
	shell_destroy(&shell);
	return (0);
}
