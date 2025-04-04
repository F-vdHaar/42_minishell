/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:49 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/04 18:06:14 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


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
			  // TODO Check if continue and break are allowed ?
			continue;
		}
		handle_argument(&tokens, &cmd_str);
	}
	log_output("[tokenize_arguments] Processing input finished ");
	return tokens;
}

void handle_argument(t_token **tokens, char **cmd_str)
{
	log_output("[handle_argument]");
	log_output(*cmd_str);
	while (**cmd_str && **cmd_str == ' ')
		(*cmd_str)++;
	if (**cmd_str == '\0') 
		return;
	char *start = *cmd_str;
	while (**cmd_str && **cmd_str != ' ' && determine_operator(*cmd_str) == NONE)
		(*cmd_str)++;

	// If we have a valid argument, create a token from it
	if (*cmd_str > start)  // Check if the argument has any length
	{
		char *token_str = ft_substr(start, 0, *cmd_str - start);
		if (!token_str)
		{
			log_error("[handle_argument] Memory allocation failed for argument token");
			free_tokens(*tokens);
			*tokens = NULL;
			return;
		}

		// Create a token for the argument and add it to the token list
		add_token(tokens, create_token(token_str, NONE));
		log_output("[handle_argument] token added");
	}

	// Skip spaces after argument
	while (**cmd_str == ' ')
		(*cmd_str)++;

	log_output("[handle_argument] finished");
}



void handle_redirection(t_token **tokens, char **cmd_str, t_operator token_type)
{
	log_output("[handle_redirection]");
	log_output(*cmd_str);

	char *token_str;
	
	// Check for two-character redirection operators (e.g., '>>', '<<')
	if (token_type == APPEND || token_type == HEREDOC)
	{
		token_str = ft_substr(*cmd_str, 0, 2); // For '>>' or '<<'
	}
	else
	{
		token_str = ft_substr(*cmd_str, 0, 1); // For single-character redirections
	}
	
	if (!token_str)
	{
		log_error("[handle_redirection] Memory allocation failed for redirection operator token");
		free_tokens(*tokens);
		*tokens = NULL;
		return;
	}

	add_token(tokens, create_token(token_str, token_type));
	free(token_str);

	// Move the pointer past the redirection operator
	*cmd_str += (token_type == APPEND || token_type == HEREDOC) ? 2 : 1;
}
void handle_operator(t_token **tokens, char **cmd_str, t_operator token_type)
{
	log_output("[handle_operator]");
	log_output(*cmd_str);
	
	// For multi-character operators like '&&', take the full operator length
	size_t len = (token_type == AND || token_type == OR) ? 2 : 1;  // '&&' and '||' are 2 chars long
	
	char *token_str = ft_substr(*cmd_str, 0, len);
	if (!token_str)
	{
		log_error("[handle_operator] Memory allocation failed for operator token");
		free_tokens(*tokens);
		*tokens = NULL;
		return;
	}

	add_token(tokens, create_token(token_str, token_type));
	free(token_str);

	// Move past the operator
	*cmd_str += len;
}



int skip_operator(char *str)
{
	if (str == NULL)
		return 0;

	// Check for multi-character operators first (&&, ||, >>, <<)
	if (ft_strnstr(str, "&&", 2) || ft_strnstr(str, "||", 2) ||
		ft_strnstr(str, ">>", 2) || ft_strnstr(str, "<<", 2))
	{
		return 2;  // Skip 2 characters for any of the above operators
	}
	
	// Check for single-character operators (|, <, >, &, ;, (, ))
	if (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>') ||
		ft_strchr(str, '&') || ft_strchr(str, ';') || ft_strchr(str, '(') ||
		ft_strchr(str, ')'))
	{
		return 1;  // Skip 1 character for any of the above operators
	}

	// If no operator found, return 0
	return 0;
}

t_operator determine_operator(char *cmd_str)
{
	log_output("[determine_operator]");
	log_output(cmd_str);

	if (!cmd_str || !*cmd_str) 
		return (NONE);

	if (ft_strncmp(cmd_str, "&&", 2) == 0)
		return (log_output("&&"), AND);
	if (ft_strncmp(cmd_str, "||", 2) == 0)
		return (log_output("||"), OR);
	if (ft_strncmp(cmd_str, ">>", 2) == 0)
		return (log_output(">>"), APPEND);
	if (ft_strncmp(cmd_str, "<<", 2) == 0)
		return (log_output("<<"), HEREDOC);
	
	if (*cmd_str == '|')
		return (log_output("|"), PIPE);
	if (*cmd_str == '<')
		return (log_output("<"), REDIR_IN);
	if (*cmd_str == '>')
		return (log_output(">"), REDIR_OUT);
	if (*cmd_str == '&')
		return (log_output("&"), BACKGROUND);
	if (*cmd_str == ';')
		return (log_output(";"), SEMICOLON);
	if (*cmd_str == '(')
		return (log_output("("), SUBSHELL_OPEN);
	if (*cmd_str == ')')
		return (log_output(")"), SUBSHELL_CLOSE);

	return (NONE);
}


t_redirection *create_redirection(t_operator type, char *file)
{
	t_redirection *redir = ft_calloc(1, sizeof(t_redirection));
	if (!redir)
	{
		log_error("[parse_tokens] Memory allocation failed for redirection node");
		return NULL;
	}

	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		log_error("[parse_tokens] Memory allocation failed for redirection file");
		free(redir);
		return NULL;
	}

	redir->type = type;
	return redir;
}
t_command *parse_tokens(t_token *tokens, t_command *commands)
{
	t_command *current_command = NULL;
	log_output("[parse_tokens]");

	// Create the first command if it's the start of the list
	if (!commands) 
	{
		current_command = create_command();
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
		log_output("[parse_tokens] Processing token:");
		log_output(tokens->value);

		if (tokens->type == AND || tokens->type == OR || tokens->type == PIPE || tokens->type == SEMICOLON)
		{
			log_output("[parse_tokens] Operator encountered, storing operator and creating new command");

			// Assign the operator to the current command
			current_command->operator = tokens->type;

			// Move to the next token (should be the start of the next command)
			tokens = tokens->next;
			if (!tokens) 
			{
				log_error("[parse_tokens] Unexpected end of input after operator");
				return commands;
			}

			// Create the next command
			t_command *next_command = create_command();
			if (!next_command) 
			{
				free_commands(commands);
				log_error("[parse_tokens] create_command failed");
				return NULL;
			}

			// Link it to the current command
			current_command->next = next_command;
			current_command = next_command;

			continue; // Skip further processing to avoid adding operator tokens as arguments
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
				tokens = tokens->next; // Skip over the file name token
			}
		}
		else 
		{
			log_output("[parse_tokens] Adding argument to command");
			log_output(tokens->value);
			add_argument_to_command(current_command, tokens->value);
		}

		// Move to the next token
		tokens = tokens->next;
		log_output("[parse_tokens] Current command state:");
		print_commands(commands);
	}

	log_output("[parse_tokens] Parsing complete");
	return commands;
}


void free_tokens(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens->next; // Store next token before freeing the current one
		free(tokens->value); // Free token string
		free(tokens); // Free token struct
		tokens = tmp; // Move to next token
	}
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
