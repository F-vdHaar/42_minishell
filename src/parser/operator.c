
#include "parser.h"

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
	if (!cmd_str || !*cmd_str) 
		return (NONE);

	if (ft_strncmp(cmd_str, "&&", 2) == 0)
		return (log_output("[determine_operator]: &&"), AND);
	if (ft_strncmp(cmd_str, "||", 2) == 0)
		return (log_output("[determine_operator]: ||"), OR);
	if (ft_strncmp(cmd_str, ">>", 2) == 0)
		return (log_output("[determine_operator]: >>"), APPEND);
	if (ft_strncmp(cmd_str, "<<", 2) == 0)
		return (log_output("[determine_operator]: <<"), HEREDOC);
	if (*cmd_str == '|')
		return (log_output("[determine_operator]: |"), PIPE);
	if (*cmd_str == '<')
		return (log_output("[determine_operator]: <"), REDIR_IN);
	if (*cmd_str == '>')
		return (log_output("[determine_operator]: >"), REDIR_OUT);
	if (*cmd_str == '&')
		return (log_output("[determine_operator]: &"), BACKGROUND);
	if (*cmd_str == ';')
		return (log_output("[determine_operator]: ;"), SEMICOLON);
	if (*cmd_str == '(')
		return (log_output("[determine_operator]: ("), SUBSHELL_OPEN);
	if (*cmd_str == ')')
		return (log_output("[determine_operator]: )"), SUBSHELL_CLOSE);

	return (NONE);
}
