#include "builtin.h"

int	builtin_cd(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	log_output("builtin_cd called\n");
	return (0);
}

int	builtin_echo(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	log_output("builtin_echo called\n");
	return (0);
}

int	builtin_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	log_output("builtin_exit called\n");
	return (0);
}