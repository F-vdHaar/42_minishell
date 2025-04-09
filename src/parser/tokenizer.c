/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:49 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/09 13:55:01 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


// Helper function to create a token and assign its value and type
t_token *create_token(char *value, t_operator type)
{
	t_token *new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		log_error("[tokenize_arguments] Memory allocation failed for token node");
		return NULL;
	}
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		log_error("[tokenize_arguments] Memory allocation failed for token value");
		free(new_token);
		return NULL;
	}
	new_token->type = type;
	return new_token;
}

// Helper function to add a token to the linked list
void add_token(t_token **head, t_token *new_token)
{
	if (!head || !new_token)
		return;
	if (*head == NULL)
	{
		*head = new_token;
		return;
	}
	t_token *current = *head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_token;
}

t_token *tokenize_arguments(char *cmd_str)
{
	log_output("[tokenize_arguments] Processing input");
	log_output(cmd_str);

	if (!cmd_str || *cmd_str == '\0')
	{
		log_error("[tokenize_arguments] Empty command string");
		return NULL;
	}

	t_token *tokens = NULL;
	t_operator token_type;

	while (*cmd_str)
	{
		while (*cmd_str == ' ')
			cmd_str++;
		token_type = determine_operator(cmd_str);
		if (token_type != NONE)
		{
			if (token_type == REDIR_IN || token_type == REDIR_OUT || token_type == APPEND || token_type == HEREDOC)
			{
				handle_redirection(&tokens, &cmd_str, token_type);
			}
			else
			{
				handle_operator(&tokens, &cmd_str, token_type);
			}
			  // TODO Check Norm if continue and break are allowed ?
			continue;
		}
		handle_argument(&tokens, &cmd_str);
	}
	log_output("[tokenize_arguments] Processing input finished ");
	return tokens;
}

t_command *parse_tokens(t_token *tokens, t_command *commands)
{
    t_command *current_command = NULL;
    log_output("[parse_tokens]");

    // Create the first command if it's the start of the list
    if (!commands) 
    {
        current_command = new_command();
        if (!current_command)
        {
            log_error("[parse_tokens] create_command failed");
            return NULL;
        }
        log_output("[parse_tokens] First command created successfully");
        commands = current_command;
    }
    else 
    {
        current_command = commands;
    }

    while (tokens)
    {
        // TODO WP Logging
        ft_printf("[parse_tokens] Processing token: [%s]", tokens->value);

        if (tokens->type == AND || tokens->type == OR || tokens->type == PIPE || tokens->type == SEMICOLON)
        {
            log_output("[parse_tokens] Operator encountered, storing operator and creating new command");
            current_command->operator = tokens->type;
            tokens = tokens->next;
            if (!tokens) 
            {
                log_error("[parse_tokens] Unexpected end of input after operator");
                return commands;
            }
            t_command *next_command = new_command();
            if (!next_command) 
            {
                free_commands(commands);
                log_error("[parse_tokens] create_command failed");
                return NULL;
            }
            current_command->next = next_command;
            current_command = next_command;

            // TODO check norm again, 
            continue;
        }
        else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == APPEND || tokens->type == HEREDOC)
        {
            log_output("[parse_tokens] Handling redirection");

            if (tokens->next && tokens->next->type == NONE)  // Ensure the next token is a filename
            {
                t_redirection *redir = create_redirection(tokens->type, tokens->next->value);
                if (!redir) 
                {
                    log_error("[parse_tokens] create_redirection failed");
                    return NULL;
                }
                current_command->redir = redir;
                log_output("[parse_tokens] Redirection added: [%s] -> [%s]", tokens->type, tokens->next->value);
                tokens = tokens->next; // Skip over the file name token
            }
        }
        else 
        {
            log_output("[parse_tokens] Adding argument to command: [%s]", tokens->value);
            add_argument_to_command(current_command, ft_strdup(tokens->value));
            log_output("[parse_tokens] Current arguments:");
            for (int i = 0; i < current_command->argc; i++) 
            {
                 // TODO WP Logging
                ft_printf("[parse_tokens]  args[%d]: [%s]", i, current_command->args[i]);
            }
        }
        tokens = tokens->next;
    }
    log_output("[parse_tokens] Parsing complete");
    return commands;
}


void free_tokens(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}


