/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:16:11 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/04 18:15:46 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h" 
# include "ft_printf.h"
# include "get_next_line.h"

# include "parser.h"

typedef struct s_redirection
{
	char				*file;
	t_operator 			type;
	int					fd;
	struct s_redirection *next;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	int					argc;
	t_redirection		*redir;
	t_operator			operator;
	int					background;
	struct s_command	*next;
}	t_command;

typedef struct s_token
{
	char			*value;
	t_operator		type;
	struct s_token	*next;
}	t_token;


extern int	g_debug_mode;

// gen_utils
void		log_error(const char *message);
void		enable_debug_mode(void);
void		log_output(const char *message);

// Commands ALL DUMMY
t_command	*new_command(char **args);
void 		add_command(t_command **head,  t_command *new_command);
void		free_commands(t_command *head);
int			execute_commands(t_command *commands);
t_command	*get_commands(char *input);

// Parser - TODO refactor files
t_token		*tokenize_arguments(char *cmd_str);

t_command	*create_command(void);




void handle_operator(t_token **tokens, char **cmd_str, t_operator token_type);
void handle_redirection(t_token **tokens, char **cmd_str, t_operator token_type);
void handle_argument(t_token **tokens, char **cmd_str);
void free_tokens(t_token *tokens);
int skip_operator(char *str);
void print_tokens(t_token *head);
void print_commands(t_command *commands);
void add_argument_to_command(t_command *command, const char *arg);
t_command *parse_tokens(t_token *tokens, t_command *commands);


#endif