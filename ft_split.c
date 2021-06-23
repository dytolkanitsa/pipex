#include "./includes/pipex.h"

static int	ft_check1(const char *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_check_lengh(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != c)
		i++;
	return (i);
}

static void	*ft_free_everything(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	**ft_writestr(char **str, char const *s, int countstr, char c)
{
	int		str_pos;
	int		n;
	int		n_elem;

	n = 0;
	str_pos = 0;
	n_elem = 0;
	while (n < countstr)
	{
		while (s[str_pos] == c)
			str_pos++;
		str[n] = (char *)malloc(ft_check_lengh((char *)s + str_pos, c) + 1);
		if (str == 0)
			ft_free_everything(str);
		while (s[str_pos] != c && s[str_pos] != 0)
			str[n][n_elem++] = s[str_pos++];
		str[n][n_elem] = 0;
		n_elem = 0;
		str_pos++;
		n++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		countstr;
	char	**str;

	if (!s)
		return (0);
	countstr = ft_check1((char *)s, c);
	str = (char **)malloc((countstr + 1) * sizeof(char *));
	if (str == 0)
		return (0);
	if (countstr == 0)
	{
		str[0] = (char *)malloc(1);
		if (str == NULL)
			ft_free_everything(str);
		str[0] = 0;
		return (str);
	}
	str = ft_writestr(str, s, countstr, c);
	str[countstr] = 0;
	return (str);
}
