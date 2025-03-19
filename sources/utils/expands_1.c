/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:28:37 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 06:43:58 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_value(t_hmap *env, const char *str, int var_len)
{
	char		*key;
	const char	*value;
	const char	**access;

	value = "";
	key = ft_substr(str, 0, var_len);
	access = hmap_get(env, key);
	if (access)
		value = *access;
	alloc_f(key);
	return (ft_strdup(value));
}

char	*expand_vars(const char *str, t_hmap *env)
{
	char	*result;
	size_t	var_len;
	size_t	last;
	size_t	i;

	i = -1;
	last = 0;
	result = NULL;
	while (str && str[++i])
	{
		var_len = (str[i] == '$') * check_ident(str + i + 1);
		var_len += (str[i] == '$' && str[i + 1] == '?');
		if (!var_len)
			continue ;
		result = ft_strjoin_f(result, ft_substr(str, last, i - last));
		result = ft_strjoin_f(result, get_var_value(env, str + i + 1, var_len));
		i += var_len;
		last = i + 1;
	}
	return (ft_strjoin_f(result, ft_substr(str, last, i - last)));
}

static int	nquote_splitting(const char *str,
				t_collection *tokens, uint32_t index)
{
	t_token	token;
	char	**split;
	int		i;

	i = -1;
	token.type = T_NQUOTE;
	split = ft_split(str, ' ');
	while (split[++i])
	{
		token.val = split[i];
		collection_insert(tokens, &token, index + i + 1);
	}
	collection_remove(tokens, index);
	alloc_f(split);
	return ((-1) * !i);
}

static int	merge_tokens(t_collection *tokens, t_collection *out)
{
	t_token			*current;
	t_token			*next;
	uint32_t		i;

	i = -1;
	while (tokens->len && ++i < tokens->len - 1)
	{
		current = collection_get(tokens, i);
		next = collection_get(tokens, i + 1);
		while (i < tokens->len - 2 && (current->type != T_NQUOTE
				|| next->type != T_NQUOTE))
		{
			current->val = ft_strjoin_f(current->val, next->val);
			current->type = next->type;
			collection_remove(tokens, i + 1);
		}
		collection_append(out, &(char *){ft_strdup(current->val)});
	}
	collection_append(out, &(char *){NULL});
	collection_destroy(tokens);
	return (out->len - 1);
}

int	expand_simple(const char *str, t_collection *out, t_hmap *env)
{
	uint32_t			i;
	t_token				*token;
	t_collection		tokens;
	const t_clear_info	clear_s = {alloc_f, T_HEAP};
	const t_clear_info	clear_t = {(void (*)(void *))token_clear, T_STACK};

	if (__builtin_expect(!str || !out || !env, 0))
		return (0);
	collection_init(out, sizeof(char **), 32, clear_s);
	collection_init(&tokens, sizeof(t_token), 32, clear_t);
	tokenize_quotes(str, &tokens);
	i = -1;
	while (tokens.len && ++i < tokens.len - 1)
	{
		token = ((t_token *)tokens.data) + i;
		if (token->type == T_SQUOTE || token->type == T_DQUOTE)
			collection_replace(&tokens, i, &(t_token){token->type,
				ft_substr(token->val, 1, ft_strlen(token->val) - 2)});
		if (token->type == T_DQUOTE || token->type == T_NQUOTE)
			collection_replace(&tokens, i, &(t_token){
				token->type, expand_vars(token->val, env)});
		if (token->type == T_NQUOTE)
			i += nquote_splitting(token->val, &tokens, i);
	}
	return (merge_tokens(&tokens, out));
}
