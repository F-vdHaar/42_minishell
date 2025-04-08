
#include "minishell.h"
# include "command.h"

t_command *generated_commands(void) {
    t_command *commands = NULL;


    //COM : MAKE SURE TO ALLOCATE ON HEAP 
    // Command 1: echo Hello World
    t_command *command1 = malloc(sizeof(t_command));
    if (command1) {
        command1->args = malloc(sizeof(char *) * 4); // 3 args + NULL
        command1->args[0] = "echo";
        command1->args[1] = "Hello";
        command1->args[2] = "World";
        command1->args[3] = NULL;

        command1->argc = 3;
        command1->operator = NONE;
        command1->background = 0;
        command1->redir = NULL;
        command1->next = NULL;

        add_command(&commands, command1);
    }

    // Command 2: ls -l |
    t_command *command2 = malloc(sizeof(t_command));
    if (command2) {
        command2->args = malloc(sizeof(char *) * 3); // 2 args + NULL
        command2->args[0] = "ls";
        command2->args[1] = "-l";
        command2->args[2] = NULL;

        command2->argc = 2;
        command2->operator = PIPE;
        command2->background = 0;
        command2->redir = NULL;
        command2->next = NULL;

        add_command(&commands, command2);
    }

    // Command 3: grep test |
    t_command *command3 = malloc(sizeof(t_command));
    if (command3) {
        command3->args = malloc(sizeof(char *) * 3); // 2 args + NULL
        command3->args[0] = "grep";
        command3->args[1] = "test";
        command3->args[2] = NULL;

        command3->argc = 2;
        command3->operator = PIPE;
        command3->background = 0;
        command3->redir = NULL;
        command3->next = NULL;

        add_command(&commands, command3);
    }

    // Command 4: cat file.txt > output.txt
    t_command *command4 = malloc(sizeof(t_command));
    if (command4) {
        command4->args = malloc(sizeof(char *) * 3); // 2 args + NULL
        command4->args[0] = "cat";
        command4->args[1] = "file.txt";
        command4->args[2] = NULL;

        command4->argc = 2;
        command4->operator = REDIR_OUT;
        command4->background = 0;
        command4->next = NULL;

        t_redirection *redir = malloc(sizeof(t_redirection));
        if (redir) {
            redir->file = strdup("output.txt");
            redir->type = REDIR_OUT;
            redir->fd = 1;
            redir->next = NULL;
            command4->redir = redir;
        } else {
            command4->redir = NULL;
        }

        add_command(&commands, command4);
    }

    // Command 5: sleep 5 &
    t_command *command5 = malloc(sizeof(t_command));
    if (command5) {
        command5->args = malloc(sizeof(char *) * 3); // 2 args + NULL
        command5->args[0] = "sleep";
        command5->args[1] = "5";
        command5->args[2] = NULL;

        command5->argc = 2;
        command5->operator = BACKGROUND;
        command5->background = 1;
        command5->redir = NULL;
        command5->next = NULL;

        add_command(&commands, command5);
    }

    return commands;
}
