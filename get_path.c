#include "./includes/pipex.h"

char	**get_path(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], "PATH=", 5) == 0))
			paths = ft_split(env[i] + 5, ':');
		i++;
	}
	return (paths);
}
