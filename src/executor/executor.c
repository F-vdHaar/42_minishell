#include "minishell.h"

static int is_builtin(char *cmd);

int	execute_commands(t_command *commands)
{
	t_command	*cmd;
	
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
		if (is_builtin(cmd->args[0]))
		{
			log_output("[execute_commands] built-in");
			// TODO execute
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

static int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!strcmp(cmd, "cd") || !strcmp(cmd, "exit") || !strcmp(cmd, "echo"));
// ... pwd 
// abort, kill raise, _exit ? 
//alias unalias history
}