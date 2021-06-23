#include "./includes/pipex.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	unsigned long int	i;

	i = 0;
	while ((i < num) && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] > str2[i] || str1[i] < str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
