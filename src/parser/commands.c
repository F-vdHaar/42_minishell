/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:12:38 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/21 07:00:51 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
// Function to create a new command node with validated arguments.
t_command *new_command(char **args)
{
	t_command *cmd;
	int argc;

	log_output("[new_command]");
	if (!args || !args[0])
		return (log_error("[new_command] Invalid arguments passed"), NULL);
	argc = 0;
	while (args[argc] != NULL)
		argc++;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (log_error("[new_command] malloc failed"), NULL);

	cmd->args = duplicate_args(args);
	if (!cmd->args)
	{
		log_error("[new_command] Argument duplication failed");
		free(cmd);
		return (NULL);
	}
	cmd->redir = NULL;  // Initialize redirection list
	cmd->next = NULL;
	return (cmd);
}


// Adds a new command to the linked list.
int add_command(t_command **head, char **args)
{
	t_command *new_cmd;

	log_output("[add_command]");
	new_cmd = new_command(args);
	if (!new_cmd)
		return (EXIT_FAILURE);
	new_cmd->next = *head;
	*head = new_cmd;

	return (EXIT_SUCCESS);
}

// Dummy function 
int	execute_commands(t_command *commands)
{
	(void)commands;
	log_output("[execute_commands] DUMMY");
	return (0);
}
t_command *create_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (log_error("[create_command] malloc failed"), NULL);

    cmd->args = NULL;
    cmd->argc = 0;
    cmd->next = NULL;

    return (cmd);
}
