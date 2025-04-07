#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

int	execute_commands(t_command *cmd_list);

#endif
