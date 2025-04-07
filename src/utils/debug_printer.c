/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:56:45 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/22 12:56:51 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token: [%s]\n", head->value);
		head = head->next;
	}
}

void	print_operator(t_command *cmd)
{
	if (cmd->operator == AND)
		printf("&&\n");
	else if (cmd->operator == OR)
		printf("||\n");
	else if (cmd->operator == PIPE)
		printf("|\n");
	else if (cmd->operator == SEMICOLON)
		printf(";\n");
}

void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		printf("  Redirection: ");
		if (redir->type == REDIR_IN)
			printf("< ");
		else if (redir->type == REDIR_OUT)
			printf("> ");
		else if (redir->type == APPEND)
			printf(">> ");
		else if (redir->type == HEREDOC)
			printf("<< ");
		printf("%s\n", redir->file);
		redir = redir->next;
	}
}

void	print_commands(t_command *cmd)
{
	int	i;

	printf("Parsed Commands:\n");
	while (cmd)
	{
		printf("-------------------------\nCommand: ");
		i = -1;
		while (++i < cmd->argc)
			printf("%s ", cmd->args[i]);
		printf("\n");
		printf("	Operator:");
		if (cmd->operator != NONE)
			print_operator(cmd);
		printf("	Redir:\n");
		print_redirections(cmd->redir);
		cmd = cmd->next;
	}
}
