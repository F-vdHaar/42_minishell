
#include "minishell.h"
# include "command.h"
# include "parser.h"

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



t_token *generated_tokens(void)
{
    t_token *tokens = NULL;

    // // Helper to append a token to the list
    // void add_token(t_token **head, const char *value, t_operator type) {
    //     t_token *new = malloc(sizeof(t_token));
    //     if (!new) return;
    //     new->value = strdup(value);
    //     new->type = type;
    //     new->next = NULL;

    //     if (!*head) {
    //         *head = new;
    //     } else {
    //         t_token *tmp = *head;
    //         while (tmp->next) tmp = tmp->next;
    //         tmp->next = new;
    //     }
    // }

    // // echo Hello World
    // add_token(&tokens, "echo", NONE);
    // add_token(&tokens, "Hello", NONE);
    // add_token(&tokens, "World", NONE);

    // // |
    // add_token(&tokens, "|", PIPE);

    // // ls -l
    // add_token(&tokens, "ls", NONE);
    // add_token(&tokens, "-l", NONE);

    // // |
    // add_token(&tokens, "|", PIPE);

    // // grep test
    // add_token(&tokens, "grep", NONE);
    // add_token(&tokens, "test", NONE);

    // // |
    // add_token(&tokens, "|", PIPE);

    // // cat file.txt > output.txt
    // add_token(&tokens, "cat", NONE);
    // add_token(&tokens, "file.txt", NONE);
    // add_token(&tokens, ">", REDIR_OUT);
    // add_token(&tokens, "output.txt", NONE);

    // // sleep 5 &
    // add_token(&tokens, "sleep", NONE);
    // add_token(&tokens, "5", NONE);
    // add_token(&tokens, "&", BACKGROUND);

    return tokens;
}