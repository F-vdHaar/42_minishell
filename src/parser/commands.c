/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:12:38 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/04 18:39:36 by fvon-der         ###   ########.fr       */
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
