/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:56:45 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/07 21:02:22 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_tokens(t_token *head)
{
	while (head)
	{
		log_output("Token: [%s]\n", head->value);
		head = head->next;
	}
}

void	print_operator(t_command *cmd)
{
	if (cmd->operator == AND)
		log_output("&&\n");
	else if (cmd->operator == OR)
		log_output("||\n");
	else if (cmd->operator == PIPE)
		log_output("|\n");
	else if (cmd->operator == SEMICOLON)
		log_output(";\n");
}

void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		log_output("  Redirection: ");
		if (redir->type == REDIR_IN)
			log_output("< ");
		else if (redir->type == REDIR_OUT)
			log_output("> ");
		else if (redir->type == APPEND)
			log_output(">> ");
		else if (redir->type == HEREDOC)
			log_output("<< ");
		log_output("%s\n", redir->file);
		redir = redir->next;
	}
}

void	print_commands(t_command *cmd)
{
	int	i;

	log_output("Parsed Commands:\n");
	while (cmd)
	{
		log_output("-------------------------\nCommand: ");
		i = -1;
		while (++i < cmd->argc)
			log_output("%s ", cmd->args[i]);
		log_output("\n");
		log_output("	Operator:");
		if (cmd->operator != NONE)
			print_operator(cmd);
		log_output("	Redir:\n");
		print_redirections(cmd->redir);
		cmd = cmd->next;
	}
}
