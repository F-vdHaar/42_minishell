/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:46:21 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/10 18:54:13 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "utils.h"
 #include "libft.h"

 // considerations 
 // 
 // double linked list ? - NO 
 // reference of raw string - why - string building maybe - NO
 typedef struct s_env {
	char *key;
	char *value;
	int exported; //pass into execve()’s environment (envp) ? / Visible to child process?
	// TODO Parser
	// int readonly; //  built-ins as readonly (like PWD, OLDPWD, SHLVLn  -  TODO decide
	int readonly;
	struct s_env *next;
} t_env;

typedef struct s_command t_command;
typedef struct s_redirection t_redirection;
typedef struct s_token t_token;
typedef enum e_operator t_operator;

 
 // operator
 t_operator determine_operator(char *cmd_str);
 void handle_operator(t_token **tokens, char **cmd_str, t_operator token_type);
 int skip_operator(char *str);
 
 
 //tokenizer
 void add_token(t_token **head, t_token *new_token);
 t_token *create_token(char *value, t_operator type);
 void free_tokens(t_token *tokens);
 t_command *parse_tokens(t_token *tokens, t_command *commands);
 t_token		*tokenize_arguments(char *cmd_str);
 
 //parser
 t_redirection *create_redirection(t_operator type, char *file);
 void handle_redirection(t_token **tokens, char **cmd_str, t_operator token_type);
 void handle_argument(t_token **tokens, char **cmd_str);
 // TODO check if needed
 int validate_input(char *input);
 
  //expander
  t_env *init_env(char **envp);
  void expand_tokens(t_token **tokens, t_env *env);
 


#endif