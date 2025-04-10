#ifndef UTILS_H
# define UTILS_H

#include <stdarg.h>
 #include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include "command.h"
#include "parser.h"



// THIS IS EXTENSIVE
#define DEBUG_NONE				0         // No debugging
#define DEBUG_GEN_ENV			1 << 0    // Debug generated environment variables
#define DEBUG_GEN_TOKENS		1 << 1    // Debug generated tokens
#define DEBUG_GEN_COMMANDS		1 << 2    // Debug generated commands
#define DEBUG_GEN_EXECUTION		1 << 3    // Debug generated commands execution
#define DEBUG_GEN_QUOTES		1 << 4    // Debug quote handling
#define DEBUG_GEN_REDIRECTS		1 << 5    // Debug redirection parsing
#define DEBUG_GEN_PIPELINES		1 << 6    // Debug pipeline parsing
#define DEBUG_GEN_ASSIGNMENTS	1 << 7    // Debug assignment parsing
#define DEBUG_EXEC_FORK			1 << 8    // Debug fork system call
#define DEBUG_EXEC_WAIT			1 << 9    // Debug wait system call
#define DEBUG_EXEC_PATH			1 << 10   // Debug command path search
#define DEBUG_EXEC_FD			1 << 11   // Debug file descriptor handling
#define DEBUG_EXEC_SIG			1 << 12   // Debug signal handling
#define DEBUG_MEM_ALLOC			1 << 13   // Debug memory allocation
#define DEBUG_RESOURCES			1 << 14   // Debug resource usage
#define DEBUG_JOB_CONTROL		1 << 15   // Debug job control logic
#define DEBUG_BG_FG				1 << 16   // Debug background/foreground process management
#define DEBUG_SIG_HANDLER		1 << 17   // Debug signal handlers
#define DEBUG_EXIT_STATUS		1 << 18   // Debug exit status
#define DEBUG_CMD_SUBST			1 << 19   // Debug command substitution
#define DEBUG_VAR_EXPANSION		1 << 20   // Debug variable expansion
#define DEBUG_SYS_INFO			1 << 21   // Debug system info
#define DEBUG_PATH				1 << 22   // Debug $PATH environment variable

#define DEBUG_ALL				 (DEBUG_GEN_ENV | DEBUG_GEN_TOKENS | DEBUG_GEN_COMMANDS | \
								 DEBUG_GEN_EXECUTION | DEBUG_GEN_QUOTES | DEBUG_GEN_REDIRECTS | \
								 DEBUG_GEN_PIPELINES | DEBUG_GEN_ASSIGNMENTS | DEBUG_EXEC_FORK | \
								 DEBUG_EXEC_WAIT | DEBUG_EXEC_PATH | DEBUG_EXEC_FD | DEBUG_EXEC_SIG | \
								 DEBUG_MEM_ALLOC | DEBUG_RESOURCES | DEBUG_JOB_CONTROL | DEBUG_BG_FG | \
								 DEBUG_SIG_HANDLER | DEBUG_EXIT_STATUS | DEBUG_CMD_SUBST | \
								 DEBUG_VAR_EXPANSION | DEBUG_SYS_INFO | DEBUG_PATH)



// Forward declarations
typedef struct s_command t_command;
typedef struct s_redirection t_redirection;
typedef struct s_token t_token;
typedef enum e_operator t_operator;
typedef struct s_env t_env;

extern int	g_debug_mode;


//debug_mode
void		enable_debug_mode(int i);
void		log_debug_mode(void);

// debug_util
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
void		print_env(t_env *env);

// generated struct lists
t_token     *generated_tokens(void);
t_command   *generated_commands(void);
t_env   *generated_env(void);


#endif