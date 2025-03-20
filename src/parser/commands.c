/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:12:38 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/20 08:57:50 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dummy function
t_command	*new_command(char **args, int operator)
{
	(void)args;
	(void)operator;
	return (NULL);
}

// Dummy function for adding a command to the list (does nothing)
void	add_command(t_command **head, char **args, int operator)
{
	(void)head;
	(void)args;
	(void)operator;
}

// Dummy function for freeing commands (does nothing)
void	free_commands(t_command *head)
{
	(void)head;
}

// Dummy function 
int	execute_commands(t_command *commands)
{
	(void)commands;
	return (0);
}

// Dummy function for getting commands from input (does nothing)
t_command	*get_commands(char *input)
{
	(void)input;
	return (NULL);
}
