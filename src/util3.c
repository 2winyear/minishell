#include "../include/minishell.h"

static int		ft_count_nbr(unsigned long nbr, int cnt)
{
	cnt++;
	if (nbr == 0)
		cnt++;
	while (nbr)
	{
		nbr /= 10;
		cnt++;
	}
	return (cnt);
}

static char		*ft_insert_nbr(unsigned long nbr, int cnt, char *str, int flag)
{
	while (--cnt)
	{
		if (nbr == 0 && flag == -1)
			str[cnt - 1] = '-';
		else
			str[cnt - 1] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				cnt;
	unsigned long	nbr;
	int				flag;

	cnt = 0;
	flag = 1;
	if (n < 0)
	{
		flag *= -1;
		nbr = (unsigned long)((long long)n * -1);
		cnt++;
	}
	else
		nbr = (unsigned long)n;
	cnt = ft_count_nbr(nbr, cnt);
	if (!(str = (char*)malloc(sizeof(char) * cnt)))
		return (NULL);
	str[cnt - 1] = 0;
	return (ft_insert_nbr(nbr, cnt, str, flag));
}
