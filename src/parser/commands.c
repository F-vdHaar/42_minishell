/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:12:38 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/07 21:53:40 by fvon-de          ###   ########.fr       */
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


t_command *create_command()
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		log_error("[create_command] Failed to allocate memory for command");
		return NULL;
	}
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->redir = NULL;
	cmd->operator = NONE;
	cmd->next = NULL;
	log_output("[create_command] Command created successfully");
	return cmd;
}

void add_argument_to_command(t_command *command, const char *arg)
{
	if (!command || !arg)
	{
		log_error("Null command or argument passed.");
		return; // Return instead of exiting for better error handling at higher levels
	}

	// Allocate or reallocate memory for the arguments
	char **new_args = realloc(command->args, sizeof(char *) * (command->argc + 1));
	if (!new_args)
	{
		log_error("Memory allocation for arguments failed.");
		return; // Return on error instead of exiting
	}

	// Assign the new argument (deep copy the string)
	new_args[command->argc] = ft_strdup(arg);  // Assuming ft_strdup allocates memory for the string
	if (!new_args[command->argc])
	{
		log_error("Memory allocation for argument failed.");
		return; // Return on error instead of exiting
	}

	// Update command args and argument count
	command->args = new_args;
	command->argc++;
}
