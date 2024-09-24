#include "../minishell.h"

static size_t	ftstrlen(const char *tab, char c)
{
	size_t	i;

	i = 0;
	while (tab[i] && tab[i] != c)
		i++;
	return (i);
}

static int	count_strings(char const *str, char c)
{
	int	i;
	int	count;
	int	in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

// static char	**ft_free(char **ptr, int j)
// {
// 	while (j >= 0)
// 		free(ptr[j--]);
// 	free(ptr);
// 	return (NULL);
// }

static char	**double_split(char **ptr, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ptr[j] = ft_substr(s, i, ftstrlen(s + i, c));
			if (ptr[j] == 0)
				return (NULL);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ptr[j] = 0;
	return (ptr);
}

char	**ft_ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = ft_malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!ptr)
		return (NULL);
	return (double_split(ptr, s, c));
}