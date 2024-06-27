#include <h/utils/log.h>
#define LOG_FILE_PATH "/var/log/poelog"

void log_to_file(const char *level, const char *file, const char *func, int line, const char *fmt, ...) {
    FILE *log_file = fopen(LOG_FILE_PATH, "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    va_list args;
    //va_start(args, fmt);

    // Get the current time
    // time_t now;
    // time(&now);
    // char *time_str = ctime(&now);
    // time_str[strlen(time_str) - 1] = '\0';  // Remove the newline character

    // Print the log message to the file
    fprintf(log_file, "[%s:%s:%d] %s: ", file, func, line, level);
    vfprintf(log_file, fmt, args);
    fprintf(log_file, "\n");

    //va_end(args);
    fclose(log_file);
}