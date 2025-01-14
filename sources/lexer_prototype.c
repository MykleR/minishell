/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_prototype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:56:40 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/14 17:07:27 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/headers/libft_string.h"
#include <stdio.h>
#include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef enum e_type
{
	WORD,         // un mot (nom de cmd, arg ect)
	PIPE,         // |
	REDIRECT_IN,  // <
	REDIRECT_OUT, // >
	BACKGROUND,   // &
	SEMICOLON,    // ;
	AND,          // &&
	OR,           // ||
	DOUBLE_QUOTE, // ""
	SINGLE_QUOTE, // ''
	WHITE_SPACE,  // Classico ascii: \t \n \v \f \r
	EOF_,         // Fin input (Different de \0 ??)
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	int				len;
}					t_token;

typedef struct s_lexer
{
	const char		*input;
	size_t			pos;
}					t_lexer;

char	*ft_sanitize(char **av)
{
	char	**start;

	start = ++av;
	while (*(av + 1))
	{
		(*av)[ft_strlen(*av)] = ' ';
		av++;
	}
	return (*start);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_token	*create_token(t_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
	{
		token->value = ft_strdup(value);
		token->len = ft_strlen(token->value);
	}
	else
	{
		token->value = NULL;
		token->len = 0;
	}
	return (token);
}

void	free_token(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

t_lexer	*lexer_init(const char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	return (lexer);
}

void	free_lexer(t_lexer *lexer)
{
	free(lexer);
}

char	get_next_lexer(t_lexer *lexer)
{
	if (lexer->input[lexer->pos] != '\0')
		return (lexer->input[lexer->pos++]);
	return ('\0');
}

char	get_lexer(t_lexer *lexer)
{
	return (lexer->input[lexer->pos]);
}

t_token	*get_next_token(t_lexer *lexer)
{
	char	current;
	size_t	start;
	size_t	len;
	char	*value;

	while (ft_isspace(get_lexer(lexer)))
		get_next_lexer(lexer);
	current = get_lexer(lexer);
	if (current == '\0')
		return (create_token(EOF_, NULL));
	if (current == '|')
	{
		get_next_lexer(lexer);
		return (create_token(PIPE, "|"));
	}
	if (current == '<')
	{
		get_next_lexer(lexer);
		return (create_token(REDIRECT_IN, "<"));
	}
	if (current == '>')
	{
		get_next_lexer(lexer);
		return (create_token(REDIRECT_OUT, ">"));
	}
	else
	{
		start = lexer->pos;
		while (!ft_isspace(get_lexer(lexer)) && ft_isalpha(get_lexer(lexer))
			&& get_lexer(lexer) != '\0')
			get_next_lexer(lexer);
		len = lexer->pos - start;
		value = ft_strndup(&lexer->input[start], len);
		return (create_token(WORD, value));
	}
}

void	run_lexer(const char *input)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = lexer_init(input);
	printf("Input: %s\n", input);
	printf("Tokens:\n");
	while ((token = get_next_token(lexer))->type != EOF_)
	{
		printf(" Type: %d ", token->type);
		if (token->value)
			printf("Value: %s \n", token->value);
		else
			printf("Value: NULL\n");
		free_token(token);
	}
	free_token(token);
	free_lexer(lexer);
}
