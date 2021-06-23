#include "./includes/pipex.h"

static char	*find_path(char *path, char *commands)
{
	char	*res;

	commands = ft_strjoin("/", commands);
	res = ft_strjoin(path, commands);
	return (res);
}

static char	*find(char **path, char **command)
{
	int		i;
	int		ope;
	char	*res;

	i = 0;
	while (path[i])
	{
		res = find_path(path[i], command[0]);
		ope = open(res, O_RDONLY);
		if (ope != -1)
			break ;
		i++;
	}
	if (ope == -1)
	{
		return (NULL);
	}
	else
		return (res);
}

static void	call_child(char **argv, char **env, int *pipefd)
{
	char	**path;
	char	**command;
	int		infile;
	char	*res;

	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	infile = open(argv[1], O_RDONLY);
	dup2(infile, 0);
	command = ft_split(argv[2], ' ');
	path = get_path(env);
	res = find(path, command);
	if (res == NULL)
	{
		perror("Try another command");
	}
	else
		execve(res, command, env);
}

static void	call_parent(char **argv, char **env, int *pipefd)
{
	char	**path;
	char	**command;
	char	*res;
	int		outfile;

	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	wait(0);
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	dup2(outfile, 1);
	command = ft_split(argv[3], ' ');
	path = get_path(env);
	res = find(path, command);
	if (res == NULL)
	{
		perror("Try another command");
	}
	else
		execve(res, command, env);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	cpid;

	if (argc < 5)
	{
		ft_putstr("Use 4 argumens!\n");
		ft_putstr("Example: ./pipex file1 cmd1 cmd2 file2\n");
		return (0);
	}
	if (pipe(pipefd) == -1)
		perror("./pipex");
	cpid = fork();
	if (cpid == -1)
		perror("fork");
	if (cpid == 0)
		call_child(argv, env, pipefd);
	else
		call_parent(argv, env, pipefd);
	return (0);
}
