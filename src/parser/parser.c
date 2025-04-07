

#include "parser.h"



int validate_input(char *input)
{
	int i;
	
	i = 0;
	log_output("[validate_input]");
	if (!input || *input == '\0')
		return (log_error("[validate_input] Empty input"), EXIT_FAILURE);
	while (input[i] != '\0')
	{
		if (input[i] == '\n')
			return (log_error("[validate_input] new line"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
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

