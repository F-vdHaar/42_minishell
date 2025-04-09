#ifndef UTILS_H
# define UTILS_H

#include <stdarg.h>
 #include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include "command.h"

// Forward declarations
typedef struct s_command t_command;
typedef struct s_redirection t_redirection;
typedef struct s_token t_token;
typedef enum e_operator t_operator;

extern int	g_debug_mode;

// debug_utils
void		enable_debug_mode(int i);
void		log_output(const char *fmt, ...);
void		log_output_msg(const char *message);
// gen_utils
void		log_error(const char *fmt, ...);
void		log_error_msg(const char *message);
void        close_log_session(void);
int         init_log_session(const char *log_filename);

// debug_printer
void        print_commands(t_command *cmd);
void        print_tokens(t_token *head);
void        print_commands(t_command *commands);
void        print_redirections(t_redirection *redir);

// generated struct lists
t_token     *generated_tokens(void);
t_command   *generated_commands(void);


#endif