# Project Work Packages
outlines the current and planned work packages
including TODOs, known issues, and design discussions.

-------------------------------------------------------------------------------

WorkPack1: Parser Branch
------------------------

Description:
Focus on building the parser, including tokenization and redirection handling.

Tasks:
- Implement tokenizer for input command lines.
- Implement support for I/O redirections ('>', '<', '>>', etc.).
- Finalize decision on script handling (multi-line input, semicolons, etc.).

- Token             WP1 Parser 
- Expander          WP2 Parser
     - Envs
     - Alias
     - Tilde Expansion
- Parse command     WP3 Parser

Comments:
- Inefficient Argument Handling:
    * Current 'add_argument_to_command()' uses 'realloc()' for each argument added.
    * This is inefficient for commands with many arguments (e.g., scripts).
- Proposed Solution:
    * Add a 'capacity' field to the 't_command' struct.
    * Allocate argument array with buffer space (e.g., chunks of 8 or 16).

-------------------------------------------------------------------------------

WorkPack2: Logging
------------------

Description:
Improve internal logging system to prevent interference between output and error logs.

Tasks:
- 'log_output()' prints garbage when used in print_commands
- ft_dprintf in libft might be at fault 
- timestamped logging.

-------------------------------------------------------------------------------

WorkPack3: Executor
-------------------

Description:
Implement the core execution logic, with support for complex pipelines and redirections.

Tasks:
- Consider the design choicce for multiple pipe handling, it matters a lot
- Support command pipelines with multiple stages ('cmd1 | cmd2 | cmd3').
- Handle combined pipelines and redirections ('cmd < input | cmd2 > output').
- Background process handling ('&').

-------------------------------------------------------------------------------

WorkPack4: Builtins
-------------------

Description:
Implement internal shell built-in commands.

Tasks:
- cd
- exit
- export, unset
- Possibly alias, which, type (depending on scope)

-------------------------------------------------------------------------------

Open Design Questions
---------------------

- Script Handling:
   

- Signal Handling:
    * When and how should signal handling be implemented?

- History:

- Error Reporting:
    * Should errors be reported per command or aggregated globally?

-------------------------------------------------------------------------------

Potential Missing Workpacks
----------------------------

WorkPack5: Testing Infrastructure
- Unit tests for tokenizer, parser, executor.
- Shell script-based integration testing.

WorkPack6: Memory Management
- Implement 'free_commands()' to clean up allocated structures.
- Run memory leak checks (e.g., valgrind).

WorkPack7: Job Control (Advanced)
- Foreground/background process groups.
- Built-ins for job control: jobs, fg, bg.

-------------------------------------------------------------------------------

Summary of Known Tasks
-----------------------

| WorkPack | Description              | Status       | Person       |
|----------|--------------------------|--------------|--------------|
| WP1      | Parser + Tokenizer       |     started  |    Frauke    |
| WP2      | Logging isolation        |     started  |    Peter     |
| WP3      | Executor + Pipes/Redir   | Not started  |              |
| WP4      | Builtin commands         | Not started  |              |
| WP5      | Testing                  | TBD          |              |
| WP6      | Memory cleanup           | TBD          |              |
| WP7      | Job Control              |              |              |

-------------------------------------------------------------------------------
