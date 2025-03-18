/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:28:37 by mykle             #+#    #+#             */
/*   Updated: 2025/03/18 05:11:14 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_value(t_hmap *env, const char *str, int var_len)
{
	char		*key;
	const char	*value;

	value = "";
	key = ft_substr(str, 0, var_len);
	if (hmap_get(env, key))
		value = *(char **)hmap_get(env, key);
	alloc_f(key);
	return (ft_strdup(value));
}

static char	*replace_vars(const char *str, t_hmap *env)
{
	char	*result;
	size_t	var_len;
	size_t	last;
	size_t	i;

	i = -1;
	last = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		var_len = (str[i] == '$') * match_ident(str + i + 1);
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

static void	nquote_splitting(const char *str, t_collection *tokens, uint32_t index)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(str, ' ');
	while (split[++i])
		collection_insert(tokens, &(t_token){T_NQUOTE, split[i]}, index + i + 1);
	alloc_f(split);
	collection_remove(tokens, index);
}

static char	**merge_tokens(t_collection *tokens, int *argc)
{
	t_collection	res;
	t_token			*current;
	t_token			*next;
	uint32_t		i;

	collection_init(&res, sizeof(char **), 32, (t_clear_info){alloc_f, T_HEAP});
	i = -1;
	while (++i < tokens->len - 1)
	{
		current = collection_get(tokens, i);
		next = collection_get(tokens, i + 1);
		while (i < tokens->len - 2 && (current->type != T_NQUOTE || next->type != T_NQUOTE))
		{
			current->val = ft_strjoin_f((char *)current->val, (char *)next->val);
			current->type = next->type;
			collection_remove(tokens, i + 1);
		}
		collection_append(&res, &(char *){ft_strdup(current->val)});
	}
	if (argc)
		*argc = res.len;
	collection_append(&res, &(char *){NULL});
	collection_destroy(tokens);
	return ((char **)res.data);
}

char	**expand_simple(const char *str, t_hmap *env, int *argc)
{
	uint32_t					i;
	t_token						*token;
	t_collection				tokens;
	static const t_clear_info	clear_t = {
		(void (*)(void *))token_clear, T_STACK};

	if (__builtin_expect(!str || !env, 0))
		return (NULL);
	collection_init(&tokens, sizeof(t_token), 32, clear_t);
	tokenize_quotes(str, &tokens);
	i = -1;
	while(++i < tokens.len - 1)
	{
		token = ((t_token *)tokens.data) + i;
		if (token->type == T_SQUOTE || token->type == T_DQUOTE)
			collection_replace(&tokens, i, &(t_token){
				token->type, ft_substr(token->val, 1, ft_strlen(token->val) - 2)});
		if (token->type == T_DQUOTE || token->type == T_NQUOTE)
			collection_replace(&tokens, i, &(t_token){
				token->type, replace_vars(token->val, env)});
		if (token->type == T_NQUOTE)
			nquote_splitting(token->val, &tokens, i);
	}
	return (merge_tokens(&tokens, argc));
}
