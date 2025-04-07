
#include "executor.h"

int	execute_commands(t_command *commands)
{
	t_command	*cmd;
	t_builtin_func func;;
	
	cmd = commands;
	log_output("[execute_commands]");
	pid_t pid;
	while(cmd)
	{
		// Pipe checking
		if (cmd->operator == PIPE)
		{
			log_output("[execute_commands] PIPE");
		}
		if ((func = get_builtin(cmd->args[0])) != NULL)
		{
			log_output("[execute_commands] built-in");
			func(cmd->argc, cmd->args);
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				log_error("[execute_commands] fork failed");
				return (-1);
			}
			else if (pid == 0)
			{
				log_output("[execute_commands] Child");
				// TODO execute
				// child processes should use _exit, as exit should just be on th main process
				// does not affect the parent’s buffered output, atexit func and fds or such
				// check redir
				// check if previous pipe
				_exit(1);
			}
			else if (pid != 0)
			{
				log_output("[execute_commands] Parent");
				waitpid(pid, NULL, 0);
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
