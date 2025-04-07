/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:46:21 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/07 21:56:37 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "utils.h"
 #include "libft.h"


 
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
 
 // command 
 t_command	*create_command(void);
 void add_argument_to_command(t_command *command, const char *arg);
 

#endif