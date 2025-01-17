/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:25 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/17 18:33:28 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "proto.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
}

void	ft_env(t_env *env)
{
	while (env->next != NULL && env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	if (env)
		printf("%s\n", env->value);
}

/**
 * Tentative de cook l'export env (graou la bagarre)
 * TODO:
 * - Init env (Grap value from envp if exist (protect env -i));
 * - Verif si une var env est presente : (Verif name ?) Si existente > join :
	+ la valeur, sinon on creer la variable et on l'ajoute ggwp
 **/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
size_t	ft_strlen(const char *str)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

char	*get_key(char *dest, char *src)
{
	while (*src && *src != '=')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

char *get_value(char *dest, char *src)
{
	while (*src && *src != '=')
		src++;
	src++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

t_env	*ft_envnew(char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*ft_envlast(t_env *lst)
{
	t_env	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_envlast(*lst);
		last->next = new;
	}
}

void	ft_add_env(void)
{
}

void	ft_export(void)
{
}
t_env	*init_env(char **ep)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	while (*ep)
	{
		ft_envadd_back(&env, ft_envnew(*ep));
		ep++;
	}
	return (env);
}

void	str_print(void *ptr, void *arg)
{
	(void)arg;
	ft_printf("%s, ", *(char **)ptr);
}

int	main(int ac, char **av, char **ep)
{
	t_collection	c;

	//	t_env	*env;
	(void)ac;
	(void)av;
	(void)ep;
	//	env = init_env(ep);
	//	ft_env(env);
	collection_create(&c, sizeof(char **), 2, alloc_f);
	collection_append(&c, &((char *){ft_strdup("Bonjour ")}));
	collection_append(&c, &((char *){ft_strdup("monde ! ")}));
	collection_append(&c, &((char *){ft_strdup("ca va ?")}));
	collection_remove(&c, 1);
	collection_iter(&c, NULL, str_print);
	collection_destroy(&c);
}
