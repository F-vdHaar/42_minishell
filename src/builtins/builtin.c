
#include "builtin.h"

static t_builtin g_builtins[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"exit", builtin_exit},
	{NULL, NULL}
};

t_builtin_func get_builtin(char *name)
{
    int i;

    i = 0;
	while(g_builtins[i].name)
     {
		if (ft_strcmp(name, g_builtins[i].name) == 0)
			return g_builtins[i].func;
        i++;
	}
	return (NULL);
}
