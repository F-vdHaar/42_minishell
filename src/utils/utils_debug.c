/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:51:18 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/10 18:43:50 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"


static FILE *g_log_file = NULL;


void	log_out_msg(const char *message)
{
	log_output("%s\n", message);
}


// Log function to write to both stderr and log file
void log_output(const char *fmt, ...)
{
    const char *debug_prefix = "[DEBUG] ";
    va_list args;

    if (g_debug_mode)
    {
        // Print to stderr
        write(STDERR_FILENO, debug_prefix, 8);
        
        va_start(args, fmt);
        ft_dprintf(STDERR_FILENO, fmt, args);  // Log to STDERR
        va_end(args);

        write(STDERR_FILENO, "\n", 1);  // Add newline for clarity

        // Print to file if the file is open
        if (g_log_file != NULL)
        {
            fprintf(g_log_file, "%s", debug_prefix);  // Prefix for logs in file
            
            va_start(args, fmt);
            vfprintf(g_log_file, fmt, args);  // Write formatted string to the log file
            va_end(args);

            fprintf(g_log_file, "\n");  // Add newline at the end
        }
        else
        {
            // If file isn't open, log an error
            write(STDERR_FILENO, "Error: Log file not open\n", 24);
        }
    }
}
int init_log_session(const char *log_filename)
{
    printf("[init_log_session] Log file path: %s\n", log_filename);  // Debugging
    if (g_log_file != NULL) {
        return 0;
    }
    g_log_file = fopen(log_filename, "a");
    if (g_log_file == NULL) {
        perror("[init_log_session] Error opening log file\n");  // More detailed error
        return -1;
    }
    return 0;
}

// Close the log file when done
void close_log_session()
{
    if (g_log_file != NULL)
    {
        fclose(g_log_file);  // Close the log file when done
        g_log_file = NULL;  // Set to NULL to avoid double-closing
    }
}