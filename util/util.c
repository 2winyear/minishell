#include "../include/minishell.h"

int     ft_isdigit(int c)
{
    if ('0' <= c && c <= '9')
        return (TRUE);
    return (FALSE);
}

int     ft_strlen(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        ;
    return (i);
}

int     ft_atoi(char *str)
{
    int num;
    int idx;

    num = 0;
    idx = -1;
    if (!str)
        return (FALSE);
    while (str[++idx])
    {
        if (!ft_isdigit(str[idx]))
            return (FALSE);
    }
    while (idx > 0)
        num = (num * 10) + '0' - str[--idx];
    return (num);
}

int     ft_nbrlen(int num)
{
    int len;

    len = 0;
    while (num)
    {
        num /= 10;
        len++;
    }
    return (len);
}

int		ft_strcmp(char *str1, char *str2)
{
	int	idx;

	idx = 0;
	while (str1[idx] && str2[idx])
	{
		if (str1[idx] != str2[idx])
			return (str1[idx] - str2[idx]);
		idx++;
	}
	if (str1[idx] || str2[idx])
		return (str1[idx] - str2[idx]);
	return (0);
}

int     ft_strncmp(char *str1, char *str2, int n)
{
    int	idx;

    idx = -1;
    while (++idx < n && str1[idx] && str2[idx])
    {
        if (str1[idx] != str2[idx])
            return (str1[idx] - str2[idx]);
    }
    return (0);
}

char    *ft_strncpy(char *line, int n)
{
  char *str;
  int i;

  str = malloc(sizeof(char) * n);
  i = -1;
  while (++i < n)
    str[i] = line[i];
  str[i] = '\0';
  return (str);
}

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (*l == 0)
		return ((char*)b);
	while (i < len && b[i])
	{
		j = 0;
		while (*(b + i + j) == *(l + j) && i + j < len)
		{
			if (l[j + 1] == '\0')
				return (char*)(b + i);
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!s1)
		return (NULL);
	cpy = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cpy)
		return (NULL);
	while (s1[i] != '\0')
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char    *ft_strndup(char *s1, int len)
{
    int     idx;
    char    *s2;

    idx = -1;
    s2 = malloc(len);
    if (!s2)
        return (NULL);
    while (++idx < len)
        s2[idx] = s1[idx];
    s2[idx] = '\0';
    return(s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char*)s1;
	len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	j = -1;
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s1[++i] != 0)
		str[i] = s1[i];
	while (s2[++j] != 0)
		str[i++] = s2[j];
	str[i] = 0;
	return (str);
}

char	*ft_strjointri(char *str1, char *str2, char *str3)
{
	char	*str;
	int		len;
	int		i;
	int		j;
	int		k;

	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	k = -1;
	while (str1[++i])
		str[i] = str1[i];
	while (str2[++j])
		str[i++] = str2[j];
	while (str3[++k])
		str[i++] = str3[k];
	str[i] = '\0';
	return (str);
}
