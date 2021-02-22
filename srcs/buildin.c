#include "minishell.h"

char	*builtin_str[] = {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit"
};

int		(*builtin_funct[]) (char **) = {
	&ft_echo,
	&ft_cd,
	&ft_pwd,
	&ft_export,
	&ft_unset,
	&ft_env,
	&ft_exit
};

int	ft_echo(char **args)
{
	(void)args;
	return 0;
}

int	ft_cd(char **args)
{
	if (chdir(args[1]) != 0)
			return 0;
	return 0;
}


int	ft_pwd(char **args)
{
	char	cwd[1024 + 1];

	(void)args;
	if (!(getcwd(cwd, 1024)))
		return 0;
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return 0;
}


int	ft_export(char **args)
{
	(void)args;
	return 0;
}

int	ft_unset(char **args)
{
	(void)args;
	return 0;
}

int	ft_env(char **args)
{
	(void)args;
	return 0;
}

int	ft_exit(char **args)
{
	exit(0);
	return 0;
}


int		execute(char **args)
{
	int		i = 0;

	while (i < 7)
	{
		if (strcmp (args[0], builtin_str[i]) == 0)
			return ((*builtin_funct[i])(args));
		i++;
	}

	// return fork_process() // to implement
	return (0);
}
