/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:49 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/21 10:37:27 by fvon-de          ###   ########.fr       */
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
    new_token->next = *head;
    *head = new_token;
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
        // Skipping any spaces between tokens
        while (*cmd_str == ' ')
            cmd_str++;

        // Check for operator first
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
            continue;  // Skip to next iteration after handling the operator
        }

        // Handle argument
        handle_argument(&tokens, &cmd_str);
    }
    return tokens;
}


void handle_argument(t_token **tokens, char **cmd_str)
{
    log_output("[handle_argument]");
    log_output(*cmd_str);

    char *start = *cmd_str;
    
    // Move until the next space or operator
    while (**cmd_str && **cmd_str != ' ' && !is_operator(*cmd_str))
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

        add_token(tokens, create_token(token_str, NONE));
        free(token_str);
    }
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



int is_operator(char *str)
{
    return (str && determine_operator(str) != NONE);
}

t_operator determine_operator(char *cmd_str)
{
	log_output("[determine_operator]");
	log_output(cmd_str);
	if (ft_strnstr(cmd_str, "&&", INT_MAX))
		return (AND);
	else if (ft_strnstr(cmd_str, "||", INT_MAX))
		return (OR);
	else if (ft_strnstr(cmd_str, ">>", INT_MAX))
		return (APPEND);
	else if (ft_strnstr(cmd_str, "<<", INT_MAX))
		return (HEREDOC);
	else if (ft_strchr(cmd_str, '|'))
		return (PIPE);
	else if (ft_strchr(cmd_str, '<'))
		return (REDIR_IN);
	else if (ft_strchr(cmd_str, '>'))
		return (REDIR_OUT);
	else if (ft_strchr(cmd_str, '&'))
		return (BACKGROUND);
	else if (ft_strchr(cmd_str, ';'))
		return (SEMICOLON);
	else if (ft_strchr(cmd_str, '('))
		return (SUBSHELL_OPEN);
	else if (ft_strchr(cmd_str, ')'))
		return (SUBSHELL_CLOSE);
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

t_command *parse_tokens(t_token *tokens)
{
    t_command *commands = NULL;
    t_command *current_command = NULL;

    while (tokens)
    {
        // Ensure there is an active command before processing tokens
        if (!current_command)
        {
            current_command = create_command();
            if (!current_command)
            {
                free_commands(commands);
                return NULL;
            }
            add_command(&commands, current_command);
        }

        if (tokens->type == PIPE || tokens->type == SEMICOLON)
        {
            // Start a new command after a PIPE or SEMICOLON
            current_command = create_command();
            if (!current_command)
            {
                free_commands(commands);
                return NULL;
            }
            add_command(&commands, current_command);
        }
        else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == APPEND || tokens->type == HEREDOC)
        {
            // Handle redirection
            if (tokens->next && tokens->next->type != NONE)  // Assuming the next token is the file name
            {
                t_redirection *redir = create_redirection(tokens->type, tokens->next->value);
                current_command->redir = redir;
                tokens = tokens->next; // Skip over the file name token
            }
        }
        else
        {
            // Handle arguments
            add_argument_to_command(current_command, tokens->value);
        }

        tokens = tokens->next;
    }

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
        exit(EXIT_FAILURE); // Exit if something is wrong with the arguments
    }

    // If this is the first argument, allocate the initial space
    if (command->argc == 0)
    {

        command->args = malloc(sizeof(char *));
    }
    else
    {

        command->args = realloc(command->args, sizeof(char *) * (command->argc + 1));
    }

    if (!command->args)
    {
        log_error("Memory allocation for arguments failed.");
        exit(EXIT_FAILURE);
    }

    // Add the new argument (deep copy the string)
    command->args[command->argc] = ft_strdup(arg);  // Assuming ft_strdup allocates memory for the string
    if (!command->args[command->argc])
    {
        log_error("Memory allocation for argument failed.");
        exit(EXIT_FAILURE);
    }

    // Increment the argument count
    command->argc++;
}