/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:12:38 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/08 13:45:12 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

// Frees all commands in the linked list
void	free_commands(t_command *head)
{
	t_command	*current;
	t_command	*next;
	int			i;

	log_output("[free_commands]");
	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				log_output("Freeing argument: ");
				log_output(current->args[i]);
				free(current->args[i]);
				i++;
			}
			free(current->args);
			log_output("Freed command arguments");
		}
		log_output("Freeing command structure");
		free(current);
		current = next;
	}
	log_output("All commands successfully freed");
}

// Adds a new command to the linked list.
void 	add_command(t_command **head,  t_command *new_command)
{
	if (!head || !new_command)
	{
		log_error("[add_command] NULL head or new_command");
		return;
	}
	if (*head == NULL)
	{
		*head = new_command;
	}
	else
	{
		t_command *current = *head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_command;
	}
	log_output("[add_command] Command added to list");
}


t_command *new_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
    {
        log_error("[new_command] Failed to allocate memory for command");
        return NULL;
    }
    cmd->args = malloc(sizeof(char *) * 10);  // Allocate memory for 10 arguments initially
    if (!cmd->args)
    {
        log_error("[new_command] Failed to allocate memory for command arguments");
        free(cmd);
        return NULL;
    }
    cmd->argc = 0;
    cmd->args_size = 10;  // Initial size of the args array
    cmd->operator = NONE;
    cmd->background = 0;
    cmd->next = NULL;

    log_output("[new_command] Command created successfully");
    return cmd;
}

void add_argument_to_command(t_command *command, const char *arg)
{
    if (!command || !arg)
    {
        log_error("Null command or argument passed.");
        return;
    }

    // Check if we need to reallocate the args array
    if (command->argc >= command->args_size)
    {
        // Double the size of the args array
        command->args_size *= 2;
        char **new_args = realloc(command->args, sizeof(char *) * command->args_size);
        if (!new_args)
        {
            log_error("Memory allocation for arguments failed.");
            return;
        }
        command->args = new_args;
        log_output("Memory reallocation successful, new args_size: %d", command->args_size);
    }

    // Assign the new argument (deep copy the string)
    command->args[command->argc] = strdup(arg);
    if (!command->args[command->argc])
    {
        log_error("Memory allocation for argument failed.");
        return;
    }

    // Log the argument added
    log_output("Added argument to command '%s': %s", command->args[0], command->args[command->argc]);

    // Increment the argument count
    command->argc++;
    command->args[command->argc] = NULL;  // NULL-terminate the argument array

    // Log the updated state of the command
    log_output("Updated command args (argc: %d) for command '%s':", command->argc, command->args[0]);
    for (int i = 0; i < command->argc; i++)
    {
        log_output("arg[%d]: %s", i, command->args[i]);
    }
}

t_command *create_command(char **args)
{
    t_command *cmd = new_command();
    if (!cmd)
        return NULL;

    // Allocate memory for args dynamically and copy strings
    int argc = 0;
    while (args[argc] != NULL)
        argc++;

    cmd->args = malloc(sizeof(char *) * (argc + 1));
    if (!cmd->args)
    {
        log_output("Failed to allocate memory for command arguments");
        free(cmd);
        return NULL;
    }

    for (int i = 0; i < argc; i++)
    {
        cmd->args[i] = strdup(args[i]);
        if (!cmd->args[i])
        {
            log_output("Failed to copy argument string");
            for (int j = 0; j < i; j++)
                free(cmd->args[j]);
            free(cmd->args);
            free(cmd);
            return NULL;
        }
    }

    cmd->args[argc] = NULL;  // Null-terminate the args array
    cmd->argc = argc;

    return cmd;
}