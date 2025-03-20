/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:49 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/20 16:30:14 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char **tokenize_arguments(char *cmd_str)
{
	log_output("[tokenize_arguments] DUMMY");

	// Dummy: return a single argument with the command itself
	char **args = malloc(2 * sizeof(char *));  // Two elements: one for the command and one for NULL
	if (!args)
	{
		log_error("[tokenize_arguments] Memory allocation failed");
		return NULL;
	}
	args[0] = ft_strdup(cmd_str);
	args[1] = NULL;
	return args;
}

t_operator determine_operator(char *cmd_str)
{
	log_output("[determine_operator] DUMMY");

	(void) cmd_str;
	// Dummy: Assume no operator found (return NONE)
	return NONE;

	// if (strchr(cmd_str, '|'))
	//     return PIPE;
	// if (strchr(cmd_str, '<'))
	//     return REDIR_IN;
	// if (strchr(cmd_str, '>'))
	//     return REDIR_OUT;
	// if (strchr(cmd_str, '&'))
	//     return BACKGROUND;
	// return NONE;
}

