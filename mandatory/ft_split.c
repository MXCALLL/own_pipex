/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:51:43 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/07 18:11:07 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*alloc_word(const char *s, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	freeall(char **words, size_t n)
{
	size_t	i;

	i = 0;
	while (n > 0)
	{
		n--;
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	words = NULL;
}

static char	*get_next_word(char const **s, char c)
{
	size_t	len;
	char	*word;

	while (**s == c)
		(*s)++;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	word = alloc_word(*s, len);
	*s += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		words[i] = get_next_word(&s, c);
		if (!words[i])
			return (freeall(words, i), NULL);
		i++;
	}
	words[i] = NULL;
	return (words);
}
