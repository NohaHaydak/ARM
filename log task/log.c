#include <stdio.h>
#include <stdarg.h>
typedef enum 
{
    LOG_OUTPUT_CONSOLE,
    LOG_OUTPUT_FILE
} logOutPutChannel_t;

void log_setOutputChannel(logOutPutChannel_t Copy_outPutChannel, const char *file_path);

void Log_write(const char *format, ...);

logOutPutChannel_t current_output_channel = LOG_OUTPUT_CONSOLE;
char log_file_path[100] = ""; 
int main() 
{
    // Set the output channel to file with a specific path
    log_setOutputChannel(LOG_OUTPUT_FILE, "F:\\Tourkey\\log task\\log.txt");
    Log_write("This will be logged to a file with a specific path.\n");

    // Set the output channel back to console
    //log_setOutputChannel(LOG_OUTPUT_CONSOLE, "");
   // Log_write("This will be logged to the console.\n");

    return 0;
}

void log_setOutputChannel(logOutPutChannel_t Copy_outPutChannel, const char *file_path) 
{
    current_output_channel = Copy_outPutChannel;
    if (current_output_channel == LOG_OUTPUT_FILE) 
    {
        snprintf(log_file_path, sizeof(log_file_path), "%s", file_path);
    }
}

void Log_write(const char *format, ...) 
{
    va_list args;
    va_start(args, format);

    switch (current_output_channel) 
    {
        case LOG_OUTPUT_FILE: 
        {
            FILE *file = fopen(log_file_path, "a");
            if (file != NULL) 
            {
                vfprintf(file, format, args);
                fclose(file);
            } else 
            {
                printf("Error opening file for logging.\n");
            }
            break;
        }
        case LOG_OUTPUT_CONSOLE:
            vprintf(format, args);
            break;
        default:
            break;
    }

    va_end(args);
}