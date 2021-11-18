#include "../include/minishell.h"

static int		ft_count(char const *s, char c)
{
	int i;
	int cnt;

	i = -1;
	cnt = 0;
	while (s[++i] == c)
		;
	while (s[i])
	{
		if (s[i] == c || s[i + 1] == 0)
		{
			cnt++;
			while (s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (cnt);
}

static char		*ft_insert_str(char *s, char c, char *str, int idx)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	s += idx;
	if (!s[i])
	{
		if (!(str = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
		str[j] = 0;
		return (str);
	}
	while (s[k] != c && s[k] != 0)
		k++;
	if (!(str = (char*)malloc(sizeof(char) * (k + 1))))
		return (NULL);
	while (j < k)
		str[j++] = *s++;
	str[j] = 0;
	return (str);
}

static char		**ft_free(char **str, int i)
{
	int idx;

	idx = -1;
	while (++idx < i)
		free(str[idx]);
	free(str);
	return (NULL);
}

static int		ft_find_c(char const *s, char c, int i)
{
	int idx;
	int cnt;

	idx = 0;
	cnt = 0;
	while (s[idx] == c)
		idx++;
	while (s[idx] && i != 0)
	{
		if (s[idx] == c)
		{
			while (s[idx + 1] == c)
				idx++;
			cnt++;
			idx++;
			if (cnt == i)
				break ;
		}
		else
			idx++;
	}
	return (idx);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		cnt;
	char	**str;

	i = -1;
	if (!s)
		return (NULL);
	else if (!c || ft_strlen((char*)s) == 0)
	{
		str = (char**)malloc(sizeof(char *));
		str[0] = 0;
		return (str);
	}
	cnt = ft_count(s, c);
	if (!(str = (char**)malloc(sizeof(char*) * (cnt + 1))))
		return (NULL);
	while (++i < cnt)
	{
		if (!(str[i] = ft_insert_str((char*)s, c, str[i], ft_find_c(s, c, i))))
			return ((ft_free(str, i)));
	}
	str[i] = 0;
	return (str);
}