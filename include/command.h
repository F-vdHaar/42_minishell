
#ifndef COMMAND_H
#define COMMAND_H

# include <stddef.h>
# include <stdlib.h>
# include <utils.h>

typedef enum e_operator
{
	NONE,
	PIPE,			// |
	REDIR_IN,		// <
	REDIR_OUT,		// >
	APPEND,			// >>
	HEREDOC,		// <<
	AND,			// &&
	OR,				// ||
	BACKGROUND,		// &   -- e.g.: sleep 5 & wait
	SEMICOLON,		// ; Seq exec -- e.g.: echo "Hello"; ls -l
	SUBSHELL_OPEN,	// (   Subshells  -- e.g.: (cd /tmp && ls)
	SUBSHELL_CLOSE// )   Subshells
}	t_operator;

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
	int					args_size; //For avoiding a lot of realloc
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

// Commands
t_command	*new_command(void);
t_command	*create_command(char **args);
void 		add_command(t_command **head,  t_command *new_command);
void		free_commands(t_command *head);
t_command	*get_commands(char *input);
 // command 
 void add_argument_to_command(t_command *command, const char *arg);
 

#endif